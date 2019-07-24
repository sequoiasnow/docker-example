# Example 3

Example 3 fixes our dependence on gcc through use of something known as multi
stage docker builds. We actually build our image in another container, and then
copy the finished executable into our production container which is as minimal
as possible. In this case we've shrunk our image size from `106MB` to `163KB`!

## Running the Example

First build the image

```sh
docker build . -t example-3
```

Then you can run it (on port 3000) using the following command

```sh
docker run -p 3000:3000 example-3:latest
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
