/**
 * @kind path-problem
 */

import codeql.ruby.AST
import TestUtilities.InlineFlowTest
import DefaultFlowTest
import PathGraph

from TaintFlow::PathNode source, TaintFlow::PathNode sink
where TaintFlow::flowPath(source, sink)
select sink, source, sink, "$@", source, source.toString()
