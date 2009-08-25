
TESTCPPGEN = testcppgen

noinst_PYTHON=$(top_builddir)/scripts/testcppgen.py

noinst_SCRIPTS = $(TESTCPPGEN)
CLEANFILES = $(TESTCPPGEN)

$(TESTCPPGEN) : 
	@echo '#!/bin/sh' > $@
	@echo '$(PYTHON) $(pkgpythondir)/testcppgen.py $$*' >> $@
