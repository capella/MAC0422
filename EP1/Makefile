default:
	cd ep1sh_source && $(MAKE)
	cp ep1sh_source/ep1sh ./ep1sh
	cd ep1_source && $(MAKE)
	cp ep1_source/ep1 ./ep1
	cd ep1sh_source && $(MAKE) clean
	cd ep1_source && $(MAKE) clean

clean:
	$(RM) ep1 ep1sh