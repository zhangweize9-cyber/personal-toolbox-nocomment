zhangweize9-cyber/personal-toolbox-nocomment
------------------------------------------------------------------------------------

Since you've come to this repository, congratulations on opening the door to a new world! This mainly stores some of my thought processes; the update frequency is irregular—sometimes ten times a day, sometimes not even once a year. This `README.txt` is simply to explain what this repository is for. Below is a directory structure; the text files corresponding to the programming languages ​​in each directory are experimental code I've written, and will be named chronologically later. For example: `2026-02-05-17-45.txt`

* IMPORTANT
- Priority One: LLVM Structural Type Analysis The core objective remains the deep auditing of isStructuralType() within the Clang/LLVM semantic analysis layer. This involves verifying recursive member validation to ensure C++20 non-type template parameter (NTTP) safety.
- Priority Two: NixOS Declarative Migration Finalizing the migration to a purely declarative NixOS environment on WSL2. The goal is to eliminate systemic errors encountered during previous Gentoo installations by defining a reproducible configuration.nix that locks down the LLVM 17 toolchain and Neovim environments.

* PLANNING
- Logic Optimization: Async UI Architecture Refining the GDB dashboard UI to utilize non-blocking asynchronous calls. Following the rejection of legacy sleep patterns in Neovim PRs, the new plan involves a reactive event loop for real-time memory visualization.
- Compiler Infrastructure: Cross-Language Tooling Building a unified Makefile system within the /bin directory to handle automatic compilation for the diverse languages present in the repository, including Zig, Rust, and Objective-C.

* SECONDARY
- Exploration: Functional Paradigms in Nix Deepening the understanding of the Nix expression language to manage complex flakes. While secondary to C++ development, it provides the "Logic Fortress" necessary for stable experimentation.
- Maintenance: Legacy Repository Cleanup Archiving "Hello World" scripts into organized sub-directories. This ensures that the nocomment philosophy remains intact by keeping the code self-documenting and structural.

* FACTORY
- Sandbox: Prototype Zero A pure testing zone for raw C++ snippets. This is where pointer-level chainings like a->b()->c() are stress-tested for null-pointer safety before being integrated into main tools.
- Sandbox: Multi-Language Syntax Tests The "Factory" handles isolated syntax verification for C#, Go, and Kotlin as seen in current repository uploads. These are treated as ephemeral logic slices to test compiler behavior across different runtime environments.
