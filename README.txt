zhangweize9-cyber/personal-toolbox-nocomment
------------------------------------------------------------------------

Introduction
Since you've come to this repository, congratulations on opening the door to a new world! This mainly stores some of my thought processes; the update frequency is irregular—sometimes ten times a day, sometimes not even once a year. 
This `README.txt` is simply to explain what this repository is for. Below is a directory structure; the text files corresponding to the programming languages in each directory are experimental code I've written, and will be named chronologically later. 
For example: `20260205-174523.txt`
2026 02    05   -            17   45     23     .txt
^^^^ ^^    ^^   ^            ^^   ^^     ^^     ^^^^
Year Month Date Segmentation Hour Minute Second File Extension

How To Check File Time
$ stat ../../LICENSE
  File: ../../LICENSE
  Size: 1079      	Blocks: 8          IO Block: 4096   regular file
Device: 8,48	Inode: 355800      Links: 1
Access: (0644/-rw-r--r--)  Uid: ( 1000/the-essence-of-life)   Gid: ( 1000/the-essence-of-life)
Access: 2026-02-01 13:22:40.408926016 +0800
Modify: 2026-02-01 13:22:40.380925998 +0800
Change: 2026-02-01 13:22:40.380925998 +0800
 Birth: 2026-02-01 13:22:40.380925998 +0800
        ^^^^^^^^^^ ^^^^^^^^
	This corresponds to the date and specific time of this document.

File Tree
. (Root Directory)
├── factory/ -> This area is mainly used to store test cases.
│   ├── bin/ -> This section primarily stores compiled binary files. 
│   └── test/ -> This section mainly contains some test files.
├── important/ -> This is the programming language I'm currently learning.
│   ├── cplusplus/ -> C++ programming language.
│   ├── lua/ -> Lua scripting language.
│   └── python/ -> Python machine learning.
├── LICENSE -> This project follows the MIT license.
├── planning/ -> No prior programming language planned for learning.
│   ├── csharp/ -> CSharp for building cross-platform applications.
│   ├── go/ -> Go is used to develop network services.
│   ├── rust/ -> Rust is used for embedded development.
│   └── zig/ -> Zig is an emerging system-level programming language.
├── README.txt -> Project Description.
└── secondary/ -> It has a basic understanding, but not enough to be used flexibly.
    ├── bash/ -> Bash is used for scripting and automation.
    ├── clang/ -> A high-performance, lightweight compiler front-end based on LLVM.
    ├── java/ -> Java is a highly portable programming language.
    ├── kotlin/ -> Kotlin can be used for cross-platform development.
    └── objectivec/ -> Objective-C is a general-purpose, object-oriented programming language.

* IMPORTANT (./important/)
- Priority One: LLVM Structural Type Analysis The core objective remains the deep auditing of isStructuralType() within the Clang/LLVM semantic analysis layer. This involves verifying recursive member validation to ensure C++20 non-type template parameter (NTTP) safety.
- Priority Two: NixOS Declarative Migration Finalizing the migration to a purely declarative NixOS environment on WSL2. The goal is to eliminate systemic errors encountered during previous Gentoo installations by defining a reproducible configuration.nix that locks down the LLVM 17 toolchain and Neovim environments.

* PLANNING (./planning/)
- Logic Optimization: Async UI Architecture Refining the GDB dashboard UI to utilize non-blocking asynchronous calls. Following the rejection of legacy sleep patterns in Neovim PRs, the new plan involves a reactive event loop for real-time memory visualization.
- Compiler Infrastructure: Cross-Language Tooling Building a unified Makefile system within the /bin directory to handle automatic compilation for the diverse languages present in the repository, including Zig, Rust, and Objective-C.

* SECONDARY (./secondary/)
- Exploration: Functional Paradigms in Nix Deepening the understanding of the Nix expression language to manage complex flakes. While secondary to C++ development, it provides the "Logic Fortress" necessary for stable experimentation.
- Maintenance: Legacy Repository Cleanup Archiving "Hello World" scripts into organized sub-directories. This ensures that the nocomment philosophy remains intact by keeping the code self-documenting and structural.

* FACTORY (./factory/)
- Sandbox: Prototype Zero A pure testing zone for raw C++ snippets. This is where pointer-level chainings like a->b()->c() are stress-tested for null-pointer safety before being integrated into main tools.
- Sandbox: Multi-Language Syntax Tests The "Factory" handles isolated syntax verification for C#, Go, and Kotlin as seen in current repository uploads. These are treated as ephemeral logic slices to test compiler behavior across different runtime environments.
