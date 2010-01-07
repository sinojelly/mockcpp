
CXXTESTPLUSGEN = cxxtestplus-gen

pkgdata_SCRIPTS=$(top_builddir)/scripts/cxxtestplus-gen.py

bin_SCRIPTS = $(CXXTESTPLUSGEN)
CLEANFILES = $(CXXTESTPLUSGEN)

$(CXXTESTPLUSGEN) : 
	@echo '#!/bin/sh' > $@
	@echo '$(PYTHON) $(pkgdatadir)/testcppgen.py $$*' >> $@
