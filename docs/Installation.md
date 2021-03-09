While configure mock++ with cmake, follow variables could be specified:

|  Variable | Type | Default Value | Scope | Notes |
|:----------|:-----|:--------------|:------|:------|
| MOCKCPP\_ALLOW\_MI | BOOL | TRUE | TRUE/FALSE | Allow multi-inheritance or not |
| MOCKCPP\_MAX\_INHERITANCE | STRING | 2 | 2~5 |maximum parents number of an interface |
| MOCKCPP\_NO\_NAMESPACE | BOOL | FALSE | TRUE/FALSE | using mockpp namespace or not |
| MOCKCPP\_MAX\_VTBL\_SIZE | STRING | 20 | 2~50 | maximum virtual table size |
| MOCKCPP\_MAX\_PARAMETERS | STRING | 12 | 1~12 | maximum number of parameters of a function/method |
| MOCKCPP\_INSTALL\_BOOST | BOOL | FALSE | TRUE/FALSE | install boost library or not while running "make install" |