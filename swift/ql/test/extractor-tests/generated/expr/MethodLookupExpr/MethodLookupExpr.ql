// generated by codegen/codegen.py
import codeql.swift.elements
import TestUtils

from MethodLookupExpr x, string hasType, Expr getBase, string hasMember, Expr getMethodRef
where
  toBeTested(x) and
  not x.isUnknown() and
  (if x.hasType() then hasType = "yes" else hasType = "no") and
  getBase = x.getBase() and
  (if x.hasMember() then hasMember = "yes" else hasMember = "no") and
  getMethodRef = x.getMethodRef()
select x, "hasType:", hasType, "getBase:", getBase, "hasMember:", hasMember, "getMethodRef:",
  getMethodRef