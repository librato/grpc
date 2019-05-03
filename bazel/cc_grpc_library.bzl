"""Generates and compiles C++ grpc stubs from proto_library rules."""

load("//bazel:generate_cc.bzl", "generate_cc")

def cc_grpc_library(
        name,
        srcs,
        deps,
        proto_only = False,
        well_known_protos = True,
        generate_mocks = False,
        use_external = False,
        grpc_only = False,
        **kwargs):
    """Generates C++ grpc classes for services defined in a proto file.

    If grpc_only is True, this rule is compatible with proto_library and
    cc_proto_library native rules such that it expects proto_library target
    as srcs argument and generates only grpc library classes, expecting
    protobuf messages classes library (cc_proto_library target) to be passed in
    deps argument. By default grpc_only is False which makes this rule to behave
    in a backwards-compatible mode (trying to generate both proto and grpc
    classes).

    Assumes the generated classes will be used in cc_api_version = 2.

    Args:
        name (str): Name of rule.
        srcs (list): A single .proto file which contains services definitions,
          or if grpc_only parameter is True, a single proto_library which
          contains services descriptors.
        deps (list): A list of C++ proto_library (or cc_proto_library) which
          provides the compiled code of any message that the services depend on.
        proto_only (bool): If True, create only C++ proto classes library,
          avoid creating C++ grpc classes library (expect it in deps).
        well_known_protos (bool): Should this library additionally depend on
          well known protos.
        generate_mocks: when True, Google Mock code for client stub is generated.
        use_external: Not used.
        grpc_only: if True, generate only grpc library, expecting protobuf
          messages library (cc_proto_library target) to be passed as deps.
        **kwargs: rest of arguments, e.g., compatible_with and visibility
    """
    if len(srcs) > 1:
        fail("Only one srcs value supported", "srcs")
    if grpc_only and proto_only:
        fail("A mutualy exclusive configuraiton is specified: grpc_only = True and proto_only = True")

    extra_deps = []

    if not grpc_only:
        proto_target = "_" + name + "_only"
        cc_proto_target = name if proto_only else "_" + name + "_cc_proto"

        proto_deps = ["_" + dep + "_only" for dep in deps if dep.find(":") == -1]
        proto_deps += [dep.split(":")[0] + ":" + "_" + dep.split(":")[1] + "_only" for dep in deps if dep.find(":") != -1]

        native.proto_library(
            name = proto_target,
            srcs = srcs,
            deps = proto_deps,
            **kwargs
        )

        native.cc_proto_library(
            name = cc_proto_target,
            deps = [":" + proto_target],
            **kwargs
        )
        extra_deps.append(":" + cc_proto_target)
    else:
        if not srcs:
            fail("srcs cannot be empty", "srcs")
        proto_target = srcs[0]

    if not proto_only:
        codegen_grpc_target = "_" + name + "_grpc_codegen"
        generate_cc(
            name = codegen_grpc_target,
            srcs = [proto_target],
            plugin = "@com_github_grpc_grpc//:grpc_cpp_plugin",
            well_known_protos = well_known_protos,
            generate_mocks = generate_mocks,
            **kwargs
        )

        native.cc_library(
            name = name,
            srcs = [":" + codegen_grpc_target],
            hdrs = [":" + codegen_grpc_target],
            deps = deps +
                   extra_deps +
                   ["@com_github_grpc_grpc//:grpc++_codegen_proto"],
            **kwargs
        )
