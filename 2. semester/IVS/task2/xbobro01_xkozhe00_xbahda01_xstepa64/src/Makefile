.PHONY: all pack test doc run profile clean create_installer install uninstall

all: main.py
	python3 main.py

pack:
	cd .. && zip -r xbobro01_xkozhe00_xbahda01_xstepa64.zip * && zip -u xbobro01_xkozhe00_xbahda01_xstepa64.zip .git .gitignore .editorconfig

test: mathlib_test.py
	python3 mathlib_test

doc: Doxyfile
	mkdir doc && cd doc && doxygen ../Doxyfile

run: main.py
	python3 main.py 

profile: profiling.py
	python3 -m cProfile -s time profiling.py < ../profiling/vstup.txt > ../profiling/vystup.txt

clean: 
	rm -rf doc && cd .. && rm install/trelico_calculator_v_1.2.deb && rm -rf install/trelico_calculator_v_1.2/usr/share/trelico_calc

create_installer: installer_ctor.sh
	bash installer_ctor.sh

install:
	sudo apt install ../install/trelico_calculator_v_1.2.deb

uninstall:
	sudo apt purge trelico-calc 
	sudo rm -rf /usr/share/trelico_calc

