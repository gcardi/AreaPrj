# AreaPrj — Build Instructions

This is a C++Builder project (`Area.cbproj`) built outside the IDE with MSBuild.

## Environment setup

Before invoking MSBuild, initialize the RAD Studio environment variables by running:

```
rsvars.bat
```

Once `rsvars.bat` has set the environment, the correct MSBuild is on `PATH`. You can confirm its location with:

```
where msbuild
```

## Compiling the project

From the project directory, build with:

```
msbuild Area.cbproj
```

## Preferred target

The preferred final target is the modern **clang-based `bcc64x` compiler (Clang 20)** in **Release** configuration.
