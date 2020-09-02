# -*- mode: ruby -*-
# vi: set ft=ruby :

$provision_base = <<-EOS
echo "Installing dependencies (phase 1)"
mkdir /home/vagrant/Prism-HTTP/build
export NWORKERS=2
export BUILD_ROOT=/home/vagrant
bash /home/vagrant/Prism-HTTP/scripts/install_deps.sh
dpkg -i /home/vagrant/Prism-HTTP/deps/linux-image-4.18.0_4.18.0-1_amd64.deb
dpkg -i /home/vagrant/Prism-HTTP/deps/linux-headers-4.18.0_4.18.0-1_amd64.deb
dpkg -i /home/vagrant/Prism-HTTP/deps/linux-image-4.18.0-dbg_4.18.0-1_amd64.deb
dpkg -i /home/vagrant/Prism-HTTP/deps/linux-libc-dev_4.18.0-1_amd64.deb
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
  end

  config.vm.define "backend1" do |node|
    node.vm.hostname = "backend1"
    node.vm.network "private_network",
      libvirt__network_name: "net1",
      libvirt__forward_mode: "veryisolated",
      libvirt__dhcp_enabled: false,
      ip: "172.16.10.12",
      mac: "02:00:00:00:00:02"
  end

  config.vm.define "backend2" do |node|
    node.vm.hostname = "backend2"
    node.vm.network "private_network",
      libvirt__network_name: "net2",
      libvirt__forward_mode: "veryisolated",
      libvirt__dhcp_enabled: false,
      ip: "172.16.10.13",
      mac: "02:00:00:00:00:03"
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
  end

  # Provision
  config.vm.provision "shell", inline: $provision_base
  config.vm.provision "reload"
end
