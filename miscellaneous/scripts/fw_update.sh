# Firewall creation script for securing a box.
# Author: Arc1t3ct
# Credit goes to nstickney for the original script that this is *heavily* based off of

set -eEuo pipefail
trap 'echo "Aborting (errexit line $LINENO). Exit code: $?" >&2' ERR
IFS=$'\n\t'

echo "Usage: ./fw_update.sh <port> .. <port>\n"
echo " Please supply a list of required ports for required services (tcp only)"

if [ ! -x "$(command -v iptables)" ]; then
    printf '%s\n' "Do you have iptables installed?"
    exit 127
fi

if [ ! -x "$(command -v sudo)" ]; then
    printf '%s\n' "This script requires sudo." >&2
    exit 127
fi

if (( "$(id -u)" == 0 )) && [ ! -z "$SUDO_COMMAND" ]; then
    printf '%s\n' "Don't run this script with sudo; it will invoke sudo as required."
    exit 1
fi

if [ -x "$(command -v systemctl)" ]; then
    sudo systemctl restart iptables
fi

save_permanent_iptables() {

	# On an Arch machine:
	if [ -x "$(command -v pacman)" ] && \
		[ -x "$(command -v iptables-save)" ]; then
		sudo iptables-save | sudo tee /etc/iptables/iptables.rules >/dev/null

	# On a CentOS machine:
	elif [ -x "$(command -v yum)" ] && \
		sudo yum list installed iptables-services >/dev/null 2>&1 ; then
		sudo service iptables save
	
	# On a Debian machine:
	elif [ -x "$(apt)" ] && dpkg -s iptables-persistent >/dev/null 2>&1; then
		sudo dpkg-reconfigure -y iptables-persistent
	
	# Otherwise, fail:
	else
		# Warn about non-persistence
		printf '\e[1;31mWARNING:\e[0m'
		printf ' The applied configuration is NOT PERMANENT across reboots. Please\n'
		printf "    consult your distribution's documentation to determine how best to\\n"
		printf '    persist these rules. Suggested tools include iptables-persistent,\n'
		printf '    iptables-save, or iptables-services.\n'
	fi
}


INTERFACE="$(ip route | grep default | awk '{print $5}')"

INTRANET="$(ip addr | grep "$INTERFACE" | awk 'FNR==2{print $2}')"

INTRANET_ADDR="$(printf '%s') "$INTRANET" | awk -F/ '{print $1}')"
if [ ! -z "${SSH_CLIENT+x}" ]; then
    SSH_ADDR="$(echo "$SSH_CLIENT" | cut -d' ' -f1)"
fi

sudo iptables -P INPUT ACCEPT
sudo iptables -P FORWARD ACCEPT
sudo iptables -P OUTPUT ACCEPT
sudo iptables -F 
sudo iptables -X

sudo iptables -N BASE
#sudo iptables -N LOG_ACCEPT
#sudo iptables -N LOG_DROP
sudo iptables -A INPUT -j BASE
sudo iptables -A FORWARD -j BASE
sudo iptables -A OUTPUT -j BASE

[ -z "${SSH_ADDR+x}" ] || sudo iptables -A INPUT -s "$SSH_ADDR" -p tcp -m tcp --dport 22 -j ACCEPT

sudo iptables -P INPUT ACCEPT
sudo iptables -P FORWARD ACCEPT
sudo iptables -P OUTPUT ACCEPT
#sudo iptables -P LOG_ACCEPT ACCEPT
#sudo iptables -P LOG_DROP DROP

# Logging rules
#sudo iptables -A LOG_ACCEPT -j LOG --log-prefix "INPUT:ACCEPT:" --log-level 6
#sudo iptables -A LOG_DROP -j LOG --log-prefix "INPUT:DROP:" --log-level 6

# ALLOW SSH
sudo iptables -A INPUT -p tcp -m tcp --dport 22 -j ACCEPT # SSH
sudo iptables -A OUTPUT -p tcp -m tcp --dport 22 -j ACCEPT # SSH

# DROP invalid packets
sudo iptables -A BASE -m state --state INVALID -j DROP

# ACCEPT existing connections
sudo iptables -A BASE -m state --state ESTABLISHED,RELATED -j ACCEPT

# ACCEPT loopback in and out
sudo iptables -A BASE -i lo -j ACCEPT
sudo iptables -A BASE -s 127.0.0.1/8 -d 127.0.0.1/8 -j ACCEPT

# jump back after base
sudo iptables -A BASE -j RETURN

# DROP host spoofing
#sudo iptables -A INPUT -s "$INTRANET_ADDR" -j DROP
#sudo iptables -A FORWARD -s "$INTRANET_ADDR" -j DROP
#sudo iptables -A FORWARD -d "$INTRANET_ADDR" -j DROP
#sudo iptables -A INPUT -d "$INTRANET_ADDR" -j DROP

# Allow ping from intranet
sudo iptables -A INPUT -s "$INTRANET" -p icmp --icmp-type 0 -j ACCEPT   # echo reply
sudo iptables -A INPUT -s "$INTRANET" -p icmp --icmp-type 3 -j ACCEPT   # unreachable
sudo iptables -A INPUT -s "$INTRANET" -p icmp --icmp-type 8 -j ACCEPT   # echo request
sudo iptables -A INPUT -s "$INTRANET" -p icmp --icmp-type 11 -j ACCEPT  # time exceeded
sudo iptables -A INPUT -s "$INTRANET" -p icmp --icmp-type 12 -j ACCEPT  # parameter problem
sudo iptables -A OUTPUT -s "$INTRANET" -p icmp --icmp-type 0 -j ACCEPT  # echo reply
sudo iptables -A OUTPUT -s "$INTRANET" -p icmp --icmp-type 8 -j ACCEPT # echo request

# Generate rules for each service needed on the machine
for port in "$@"
do
    # Create rules for ports given through command line
    sudo iptables -A INPUT -p tcp -m tcp --dport "$port" -j ACCEPT
    sudo iptables -A OUTPUT -p tcp -m tcp --dport "$port" -j ACCEPT
done

# General UDP services
sudo iptables -A OUTPUT -p udp -m udp --dport 53 -j ACCEPT
sudo iptables -A INPUT -p udp -m upd --dport 53 -j ACCEPT
sudo iptables -A OUTPUT -p udp -m udp --dport 123 -j ACCEPT

# Default policy
#sudo iptables -A INPUT -m state --state NEW -j DROP
#sudo iptables -A OUTPUT -m state --state NEW -j DROP

# Fast DHCP from intranet
#sudo iptables -A INPUT -s "$INTRANET" -p udp -m udp --dport 5353 -j ACCEPT


sudo iptables -P INPUT DROP
sudo iptables -P FORWARD DROP
sudo iptables -P OUTPUT DROP

printf '%s\n' "Saving Iptables Rules..."
save_permanent_iptables
printf '%s\n' "IPTables saved!"

# Cleanup
printf '\n\e[1;32m%s\e[0m\n\n' "IPTables rules implemented:"
sudo iptables -L
printf '\n'
#printf '%s\n' "Note: These rules are not persistent across reboots"
