/**
 * @name Hash Algorithms
 * @description Finds all potential usage of cryptographic hash algorithms using the supported libraries.
 * @kind problem
 * @id cpp/quantum-readiness/cbom/hash-algorithms
 * @problem.severity error
 * @precision high
 * @tags security
 *       cbom
 *       cryptography
 */

import cpp
import experimental.crypto.Concepts

from HashAlgorithm alg
select alg, "Use of algorithm " + alg.getName()
