/**
 * @name Symmetric Encryption Algorithms
 * @description Finds all potential usage of symmetric encryption algorithms using the supported libraries.
 * @kind problem
 * @id cpp/quantum-readiness/cbom/symmetric-encryption-algorithms
 * @problem.severity error
 * @precision high
 * @tags security
 *       cbom
 *       cryptography
 */

import cpp
import experimental.crypto.Concepts

from SymmetricEncryptionAlgorithm alg
select alg, "Use of algorithm " + alg.getEncryptionName()
