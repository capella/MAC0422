default:
	cd ep1sh_source && $(MAKE)
	cp ep1sh_source/ep1sh ./ep1sh
	cd ep1_source && $(MAKE)
	cp ep1_source/ep1 ./ep1
	make clean2

clean:
	find ./ -name ".DS_Store" -depth -exec rm {} \;
	find ./ -name *.dSYM -depth -exec rm {} \;
	$(RM) ep1 ep1sh

clean2:
	cd ep1sh_source && $(MAKE) clean
	cd ep1_source && $(MAKE) clean

build:
	make default
	make clean
	mkdir ep1-gabriel-luis
	cp -r Makefile ep1-gabriel-luis/Makefile
	cp -r ep1sh_source ep1-gabriel-luis/ep1sh_source
	cp -r ep1_source ep1-gabriel-luis/ep1_source
	cp -r README.md ep1-gabriel-luis/LEIAME.txt
	cp -r slides/slide.pdf ep1-gabriel-luis/apresentacao.pdf
	tar -czvf ep1-gabriel-luis.tar.gz ep1-gabriel-luis
	rm -rf ep1-gabriel-luis
