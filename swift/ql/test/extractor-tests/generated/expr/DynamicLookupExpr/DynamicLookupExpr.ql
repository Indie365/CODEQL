// generated by codegen/codegen.py
import codeql.swift.elements
import TestUtils

from DynamicLookupExpr x, Expr getBase
where
  toBeTested(x) and
  not x.isUnknown() and
  getBase = x.getBase()
select x, x.getPrimaryQlClasses(), "getBase:", getBase
