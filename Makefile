SUBDIRS:=wireless_tools.rtl.3411b lib/ul_lib busybox-1.13 udhcp-0.9.8 boa-0.94.13/src iptables-1.4.10 bridge-utils-1.1/libbridge bridge-utils-1.1/brctl smtpclient captcha

PHONY := all $(SUBDIRS)
all: $(SUBDIRS)
	@echo -e "\nDone!\n"

$(SUBDIRS):
	echo "========================================================================"
	echo -e "\033[32m$$i\033[0m"
	echo "------------------------------------------------------------------------"
	$(MAKE) -C $@

PHONY += clean
clean:
	for i in $(SUBDIRS) ; do \
		echo -e "\033[31m$$i\033[0m"; \
		$(MAKE) -C $$i clean; \
	done

.PHONY: $(PHONY)
