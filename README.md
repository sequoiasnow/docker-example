# Example 1

Example 1 contains the simplest implementation of our simple echo server. It
spits out a hello world message for every incoming request. We have a simple
docker container which builds the binary and runs it.

## Running the Example

First build the image

```sh
docker build . -t example-1
```

Then you can run it (on port 3000) using the following command

```sh
docker run -p 3000:3000 example-1:latest
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

    - The CMOD command is executed on a seperate caching layer
    - There is no way to stop our program
    - Our image contains gcc even though we don't actually need it to run
      our program
