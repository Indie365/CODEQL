package com.semmle.js.extractor;

import com.semmle.util.data.UnitParser;
import com.semmle.util.exception.UserError;
import com.semmle.util.process.Env;
import com.semmle.util.process.Env.Var;

public class EnvironmentVariables {
  public static final String CODEQL_EXTRACTOR_JAVASCRIPT_ROOT_ENV_VAR =
      "CODEQL_EXTRACTOR_JAVASCRIPT_ROOT";

  public static final String CODEQL_EXTRACTOR_JAVASCRIPT_SCRATCH_DIR_ENV_VAR =
      "CODEQL_EXTRACTOR_JAVASCRIPT_SCRATCH_DIR";

  public static final String LGTM_WORKSPACE_ENV_VAR =
      "LGTM_WORKSPACE";

  public static final String CODEQL_EXTRACTOR_JAVASCRIPT_WIP_DATABASE_ENV_VAR =
      "CODEQL_EXTRACTOR_JAVASCRIPT_WIP_DATABASE";

  public static final String CODEQL_DIST_ENV_VAR = "CODEQL_DIST";

  /**
   * Returns a number of megabytes by reading an environment variable with the given suffix,
   * or the default value if not set.
   * <p>
   * The following prefixes are tried:
   * <code>CODEQL_EXTRACTOR_JAVASCRIPT_</code>,
   * <code>LGTM_</code>,
   * <code>SEMMLE_</code>.
   */
  public static int getMegabyteCountFromPrefixedEnv(String suffix, int defaultValue) {
    String envVar = "CODEQL_EXTRACTOR_JAVASCRIPT_" + suffix;
    String value = Env.systemEnv().get(envVar);
    if (value == null || value.length() == 0) {
      envVar = "LGTM_" + suffix;
      value = Env.systemEnv().get(envVar);
    }
    if (value == null || value.length() == 0) {
      envVar = "SEMMLE_" + suffix;
      value = Env.systemEnv().get(envVar);
    }
    if (value == null || value.length() == 0) {
      return defaultValue;
    }
    Integer amount = UnitParser.parseOpt(value, UnitParser.MEGABYTES);
    if (amount == null) {
      throw new UserError("Invalid value for " + envVar + ": '" + value + "'");
    }
    return amount;
  }

  /**
   * Gets the extractor root based on the <code>CODEQL_EXTRACTOR_JAVASCRIPT_ROOT</code> or <code>
   * SEMMLE_DIST</code> or environment variable, or <code>null</code> if neither is set.
   */
  public static String tryGetExtractorRoot() {
    String env = Env.systemEnv().getNonEmpty(CODEQL_EXTRACTOR_JAVASCRIPT_ROOT_ENV_VAR);
    if (env != null) return env;
    env = Env.systemEnv().getNonEmpty(Var.SEMMLE_DIST);
    if (env != null) return env;
    return null;
  }

  /**
   * Gets the extractor root based on the <code>CODEQL_EXTRACTOR_JAVASCRIPT_ROOT</code> or <code>
   * SEMMLE_DIST</code> or environment variable, or throws a UserError if neither is set.
   */
  public static String getExtractorRoot() {
    String env = tryGetExtractorRoot();
    if (env == null) {
      throw new UserError("SEMMLE_DIST or CODEQL_EXTRACTOR_JAVASCRIPT_ROOT must be set");
    }
    return env;
  }

  /**
   * Gets the scratch directory from the appropriate environment variable.
   */
  public static String getScratchDir() {
    String env = Env.systemEnv().getNonEmpty(CODEQL_EXTRACTOR_JAVASCRIPT_SCRATCH_DIR_ENV_VAR);
    if (env != null) return env;
    env = Env.systemEnv().getNonEmpty(LGTM_WORKSPACE_ENV_VAR);
    if (env != null) return env;

    throw new UserError(CODEQL_EXTRACTOR_JAVASCRIPT_SCRATCH_DIR_ENV_VAR + " or " + LGTM_WORKSPACE_ENV_VAR + " must be set");
  }

  public static String getCodeQLDist() {
    return Env.systemEnv().getNonEmpty(CODEQL_DIST_ENV_VAR);
  }

  /** Gets the output database directory. */
  public static String getWipDatabase() {
    return Env.systemEnv().getNonEmpty(CODEQL_EXTRACTOR_JAVASCRIPT_WIP_DATABASE_ENV_VAR);
  }
}
