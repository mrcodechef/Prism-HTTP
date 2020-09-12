# -*- mode: ruby -*-
# vi: set ft=ruby :

#
# Minimal network environment to make Prism work
#

$provision_base1 = <<-EOS
echo "Installing dependencies (phase 1)"
export NWORKERS=`nproc`
export BUILD_ROOT=/home/vagrant
bash /home/vagrant/Prism-HTTP/scripts/install_deps.sh
dpkg -i /home/vagrant/Prism-HTTP/deps/linux-image-4.18.0_4.18.0-1_amd64.deb
dpkg -i /home/vagrant/Prism-HTTP/deps/linux-headers-4.18.0_4.18.0-1_amd64.deb
dpkg -i /home/vagrant/Prism-HTTP/deps/linux-image-4.18.0-dbg_4.18.0-1_amd64.deb
dpkg -i /home/vagrant/Prism-HTTP/deps/linux-libc-dev_4.18.0-1_amd64.deb
EOS

$provision_base2 = <<-EOS
echo "Installing dependencies (phase2)"
export NWORKERS=`nproc`
export BUILD_ROOT=/home/vagrant

cd $BUILD_ROOT

cd netmap
./configure --drivers=virtio_net.c
make -j $NPROC
make install
cd ../

cd creme
make
cd ../

cd Prism-HTTP
cd switch
make
EOS

$provision_switch = <<-EOS
echo "Provisioning switch-specific part (phase 2)"
export NWORKERS=`nproc`
export BUILD_ROOT=/home/vagrant

cd $BUILD_ROOT

cd netmap
insmod netmap.ko

# Don't do this separately. Otherwise, we'll lose the ssh connection.
rmmod virtio_net && insmod virtio_net.c/virtio_net.ko
cd ../

vale-ctl -a vale0:eth1
vale-ctl -a vale0:eth2
vale-ctl -a vale0:eth3
vale-ctl -a vale0:eth4

cd Prism-HTTP
cd switch
make
cd kern_src
NSRC=/home/vagrant/netmap make
insmod vale-bpf-native-vale0.ko
cd ../../
EOS

$provision_prism_node = <<-EOS
echo "Provisioning frontend-specific part (phase 2)"
export NWORKERS=`nproc`
export BUILD_ROOT=/home/vagrant

cd $BUILD_ROOT

cd creme
insmod creme.ko
cd ../

cd Prism-HTTP
cd src
make -j $NPROC
make install
EOS

Vagrant.configure("2") do |config|
  config.vm.box = "generic/ubuntu1804"

  config.vm.provider "libvirt" do |v|
    v.memory = 4096
    v.cpus = 2
  end

  # Copy source directory to VM. Shared filesystem doesn't work for custom kernel.
  config.vm.synced_folder ".", "/vagrant", disabled: true
  config.vm.provision "file", source: "./", destination: "/home/vagrant/Prism-HTTP"

  config.vm.define "frontend1" do |node|
    node.vm.hostname = "frontend1"
    node.vm.network "private_network",
      libvirt__network_name: "net0",
      libvirt__forward_mode: "veryisolated",
      libvirt__dhcp_enabled: false,
      ip: "172.16.10.11",
      mac: "02:00:00:00:00:01"
    # Provision
    node.vm.provision "shell", inline: $provision_base1
    node.vm.provision "reload"
    node.vm.provision "shell", inline: $provision_base2
    node.vm.provision "shell", inline: $provision_prism_node
  end

  config.vm.define "backend1" do |node|
    node.vm.hostname = "backend1"
    node.vm.network "private_network",
      libvirt__network_name: "net1",
      libvirt__forward_mode: "veryisolated",
      libvirt__dhcp_enabled: false,
      ip: "172.16.10.12",
      mac: "02:00:00:00:00:02"
    # Provision
    node.vm.provision "shell", inline: $provision_base1
    node.vm.provision "reload"
    node.vm.provision "shell", inline: $provision_base2
    node.vm.provision "shell", inline: $provision_prism_node
  end

  config.vm.define "backend2" do |node|
    node.vm.hostname = "backend2"
    node.vm.network "private_network",
      libvirt__network_name: "net2",
      libvirt__forward_mode: "veryisolated",
      libvirt__dhcp_enabled: false,
      ip: "172.16.10.13",
      mac: "02:00:00:00:00:03"
    # Provision
    node.vm.provision "shell", inline: $provision_base1
    node.vm.provision "reload"
    node.vm.provision "shell", inline: $provision_base2
    node.vm.provision "shell", inline: $provision_prism_node
  end

  config.vm.define "client" do |node|
    node.vm.hostname = "client"
    node.vm.network "private_network",
      libvirt__network_name: "net3",
      libvirt__forward_mode: "veryisolated",
      libvirt__dhcp_enabled: false,
      ip: "172.16.10.14",
      mac: "02:00:00:00:00:04"
  end

  config.vm.define "switch" do |node|
    node.vm.hostname = "switch"
    node.vm.network "private_network",
      libvirt__network_name: "net0",
      libvirt__forward_mode: "veryisolated",
      libvirt__dhcp_enabled: false
    node.vm.network "private_network",
      libvirt__network_name: "net1",
      libvirt__forward_mode: "veryisolated",
      libvirt__dhcp_enabled: false
    node.vm.network "private_network",
      libvirt__network_name: "net2",
      libvirt__forward_mode: "veryisolated",
      libvirt__dhcp_enabled: false
    node.vm.network "private_network",
      libvirt__network_name: "net3",
      libvirt__forward_mode: "veryisolated",
      libvirt__dhcp_enabled: false
    # Provision
    node.vm.provision "shell", inline: $provision_base1
    node.vm.provision "reload"
    node.vm.provision "shell", inline: $provision_base2
    node.vm.provision "shell", inline: $provision_switch
  end
end
