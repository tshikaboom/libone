libone
=

This is a library try to parse OneNote files.
It currently does not do much, besides parsing structures and verifying they are well present in the file (mostly, they are, because we use OneNote-generated files to test this stuff, as that is all we have). The library is based around `librevenge`, as the goal would be to have something imported to LibreOffice Draw & co.

Inspiration
=
The file format is contained in two references, [[MS-ONE]](https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-one) and [[MS-ONESTORE]](https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-onestore). The latter is currently being worked on, as the storage part is still to be finished. The former would be more interesting, as it contains the meat of what the user does with the document.

The file format itself is structured in transactions and revisions (think of git) which themselves contain the user data. We currently parse the header, the root file node list and its file nodes, and would try to parse object spaces after that.

These documents depend on other reference documents provided by Microsoft (for CRC checking algorithms, primitive type sizes and whatnot).

Contributing
=
Please do! Code clean-ups would be much appreciated, as C++ is not the thing I'm good at. Otherwise, reading the refereneces and implementing them is the way to go, so this stuff would be straightforward, if not time-consuming.

Building and testing
=
This is an meson-based project. As such, invoking
```
meson build
ninja -C build
```
would suffice to get this build. After that, doing `./src/conv/raw/one2raw <file.one>` would get you some output.

To run the tests, make sure that your build directory has been configured with tests to be build (currently by default on)
Then, change into your build directory and run:
```
cd build
meson test all_tests
```


Licence
=
The library is available under MPL 2.0+, as other librevenge-based projects are.
