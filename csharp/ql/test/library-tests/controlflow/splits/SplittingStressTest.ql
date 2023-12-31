import csharp

query predicate countSplits(ControlFlowElement cfe, int i) {
  not cfe.fromLibrary() and
  i = strictcount(ControlFlow::Nodes::ElementNode n | n.getAstNode() = cfe)
}

query predicate ssaDef(Ssa::Definition def) { any() }
