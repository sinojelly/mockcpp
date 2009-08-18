
TESTCPPGEN = testcppgen

pkgpython_PYTHON=$(top_builddir)/scripts/testcppgen.py

bin_SCRIPTS = $(TESTCPPGEN)
CLEANFILES = $(TESTCPPGEN)

$(TESTCPPGEN) : 
	@echo '#!/bin/sh' > $@
	@echo '$(PYTHON) $(pkgpythondir)/testcppgen.py $$*' >> $@
