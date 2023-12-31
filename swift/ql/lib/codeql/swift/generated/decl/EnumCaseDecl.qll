// generated by codegen/codegen.py
private import codeql.swift.generated.Synth
private import codeql.swift.generated.Raw
import codeql.swift.elements.decl.Decl
import codeql.swift.elements.decl.EnumElementDecl

module Generated {
  class EnumCaseDecl extends Synth::TEnumCaseDecl, Decl {
    override string getAPrimaryQlClass() { result = "EnumCaseDecl" }

    /**
     * Gets the `index`th element of this enum case declaration (0-based).
     */
    EnumElementDecl getElement(int index) {
      result =
        Synth::convertEnumElementDeclFromRaw(Synth::convertEnumCaseDeclToRaw(this)
              .(Raw::EnumCaseDecl)
              .getElement(index))
    }

    /**
     * Gets any of the elements of this enum case declaration.
     */
    final EnumElementDecl getAnElement() { result = this.getElement(_) }

    /**
     * Gets the number of elements of this enum case declaration.
     */
    final int getNumberOfElements() { result = count(int i | exists(this.getElement(i))) }
  }
}
