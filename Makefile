#
# weizili
#
# Please use gmake but not make in FreeBSD OS
#

		
SUBDIRS := ini_parser proxy_url  string  vector

all: 
	for t in $(SUBDIRS); do $(MAKE) -C $$t ; done

check: 
	for t in $(SUBDIRS); do $(MAKE) check -C $$t ; done
	
clean:
	for t in $(SUBDIRS); do $(MAKE) clean -C $$t; done

.PHONY: clean all check 

