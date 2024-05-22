!#/bin/bash

VCAN_INTERFACE="vcan0"
MTU_SIZE="16"


modprobe vcan

if ["$EUID" -ne 0]; then
    echo "Run this script as root. Exiting..."
    exit 1
fi

# Load the vcan module
echo "Loading vcan module..."
modprobe vcan

if ! lsmod | grep -q vcan; then 
    echo "Failed to load vcan kernel module. Exiting..."
    exit 1
fi

# Create the virtual CAN interface
echo "Creating virtual CAN interface $VCAN_INTERFACE..."
ip link add dev $VCAN_INTERFACE type vcan

# Check to see if interface was created correctly
if ! ip link show $VCAN_INTERFACE > /dev/null 2>&1; then
    echo "Failed to create vcan interface. Exiting..."
    exit 1
fi

# Set the maximum transmission unit size 
ip link set $VCAN_INTERFACE mtu $MTU_SIZE

# Bring up the virtual CAN interface
echo "Bringing up virtual CAN interface $VCAN_INTERFACE..."
ip link set up $VCAN_INTERFACE

# Verify the virtual CAN interface is up
if ! ip link show $VCAN_INTERFACE | grep -q "state DOWN"; then
  echo "Virtual CAN interface $VCAN_INTERFACE is up and running."
else
  echo "Failed to bring up virtual CAN interface $VCAN_INTERFACE. Exiting."
  exit 1
fi

echo "Virtual CAN interface setup complete."