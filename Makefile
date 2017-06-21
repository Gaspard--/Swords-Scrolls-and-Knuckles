install:
	rm -rf ~/.froot/ssk
	mkdir -p ~/.froot/ssk/
	cp ssk ~/.froot/ssk/ssk
	cp lib.tar ~/.froot/ssk/lib.tar
	tar xvf lib.tar -C ~/.froot/ssk/
	echo 'export LD_LIBRARY_PATH="~/.froot/ssk/"' >> ~/.bashrc

install-yaourt:
	yaourt -Sy ogre boost openal freealut libogg ois pybind11

install-dnf:
	dnf install pybind11-devel python-devel ogre-devel ois-devel ogre-overlay libogg-devel libvorbis-devel freealut-devel ois-devel
