## [psocksxx] doc/

# doxygen
if HAVE_DOXYGEN

doxygen.stamp:
	$(DOXYGEN) doxygen.cfg
	echo timestamp > doxygen.stamp

CLEANFILES = doxygen.stamp

doxygen-doc: doxygen.stamp

install-doxygen-doc: doxygen-doc
	$(INSTALL) -d $(docdir)
	cp -r doxygen/html $(docdir)

uninstall-local:
	rm -rf $(docdir)/html

clean-local:
	rm -rf $(top_builddir)/doc/doxygen


.PHONY: doxygen-doc install-doxygen-doc

endif

