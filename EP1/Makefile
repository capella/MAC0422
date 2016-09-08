default:
	cd ep1sh_source && $(MAKE)
	cp ep1sh_source/ep1sh ./ep1sh
	cd ep1_source && $(MAKE)
	cp ep1_source/ep1 ./ep1
	make clean2

clean:
	find ./ -name ".DS_Store" -depth -exec rm {} \;
	$(RM) ep1 ep1sh

clean2:
	cd ep1sh_source && $(MAKE) clean
	cd ep1_source && $(MAKE) clean
# ./ep1 1 slides/graphs/testes_capella/10/11 /dev/null c