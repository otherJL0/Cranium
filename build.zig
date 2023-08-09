const std = @import("std");

pub fn build(b: *std.Build) void {
    const tests = .{
        "matrix",
        "function",
        "layer",
        "network",
        "optimizer",
    };

    const all_tests_step = b.step("test", "Run all tests");
    inline for (tests) |name| {
        const test_name = std.fmt.comptimePrint("{s}_tests", .{name});
        const test_file = std.fmt.comptimePrint("tests/{s}_tests.c", .{name});
        const exe = b.addExecutable(.{
            .name = test_name,
        });
        exe.addCSourceFile(.{ .file = .{ .path = test_file }, .flags = &[_][]const u8{
            "-std=c99",
            "-Wall",
            "-Wno-unused-function",
        } });
        exe.linkSystemLibrary("m");
        exe.addIncludePath(.{ .path = "src" });

        const run_cmd = b.addRunArtifact(exe);
        const test_step = b.step(test_name, "Run " ++ test_name);
        test_step.dependOn(&run_cmd.step);
        all_tests_step.dependOn(&run_cmd.step);
    }
}
