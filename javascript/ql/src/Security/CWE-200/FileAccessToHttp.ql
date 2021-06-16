/**
 * @name File data in outbound network request
 * @description Directly sending file data in an outbound network request can indicate unauthorized information disclosure.
 * @kind path-problem
 * @problem.severity warning
 * @security-severity 3.6
 * @precision medium
 * @id js/file-access-to-http
 * @tags security
 *       external/cwe/cwe-200
 */

import javascript
import semmle.javascript.security.dataflow.FileAccessToHttp::FileAccessToHttp
import DataFlow::PathGraph

from Configuration cfg, DataFlow::PathNode source, DataFlow::PathNode sink
where cfg.hasFlowPath(source, sink)
select sink.getNode(), source, sink, "$@ flows directly to outbound network request",
  source.getNode(), "File data"
