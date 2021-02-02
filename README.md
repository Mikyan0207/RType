# R-Type

<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Usage](#usage)
* [License](#license)



<!-- ABOUT THE PROJECT -->
## About The Project

R-Type is a horizontal-scrolling shooter arcade game.


### Built With

* C++17
* SFML
* protobuf
* conan


<!-- USAGE -->
## Usage

1. Download [Conan Package Manager](https://conan.io/)

2. Add Bincrafter remote for Conan

```$ conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan```

3. Build project

```mkdir build && cd build && conan install .. --build=missing && cmake .. -G "Unix Makefile" && cmake --build .```

4. Start server

```./rtype-server```

5. Start client

```./rtype-client```

<!-- LICENSE -->
## License

Distributed under the [MIT License][license-url]. See `LICENSE` for more information.


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[license-url]: https://github.com/mikyan0207/RType/blob/master/LICENSE
