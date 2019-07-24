# Example 2

Example 2 fixes our caching problem by combining the step for modifying the
executable file with the build step. This way we have one less "layer" stored
in our Docker cake, and in turn a faster and smaller build.

## Running the Example

First build the image

```sh
docker build . -t example-2
```

Then you can run it (on port 3000) using the following command

```sh
docker run -p 3000:3000 example-2:latest
```

You'll notice that there is no easy way to stop the container from running,
that's because our program has no explicit handler for `^C`. We'll fix that in
the future. For now to stop the program run

```sh
docker rm [name of your container]
```

where `[name of your container]` is the name of your container found when
looking at `docker ps`.



## Problems

There are still several points of improvement for our container.

    - There is no way to stop our program
    - Our image contains gcc even though we don't actually need it to run
      our program
