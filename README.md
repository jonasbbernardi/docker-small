
# Introdução

Files to generate the lesser possible docker image.

Tamanho: 76.48 Kb

# Setup

To generate image, first compile the `hello.c` file, to do this, build an image using `Dockerfile-compiler` file.

Next create a container from generated image.

Then, copy file from container to local machine.

At last, build an image using the `Dockerfile` file.

**Commands:**

```bash
# Build image using Dockerfile-compiler
docker build -f Dockerfile-compiler -t my-compiler .
# Create extract-hello container
docker create --name extract-hello my-compiler
# Copy the "hello" file from container
docker cp extract-hello:/hello ./hello
# Remove extract-hello container
docker rm extract-hello
# And compiler image
docker image rm my-compiler:latest
# Build image usign Dockerfile
docker build -t lesser-image .
# To test, run the image with "rm" parameter*
docker run --rm lesser-image
```

\* _The rm parameter is used to remove the container after its execution._

# AWS ECR

To send image to AWS ECR, install aws cli, login to ECR and use build/push commands, as per the following example.

```bash
# Log in docker to ECR
aws ecr get-login-password --region region | docker login --username AWS --password-stdin aws_account_id.dkr.ecr.region.amazonaws.com
# Build image with tag latest pointing to ECR
docker build -t aws_account_id.dkr.ecr.region.amazonaws.com/my-repository:latest .
# Publish image with latest tag
docker push aws_account_id.dkr.ecr.region.amazonaws.com/my-repository:latest
```

# Azure ACR

To send image to Azure ACR, install azure cli, login to ACR and use build/push commands, as per the following example.

```bash
# Log in docker to ACR
az acr login --name acr-name
# Build image with tag latest pointing to ACR
docker build -t acr-name.azurecr.io/image-name:latest .
# Publish image with latest tag
docker push acr-name.azurecr.io/image-name:latest
```

# References

- [Docker Scratch Image][docker-scratch]
- [Docker Alpine Image][docker-alpine]
- [C Hello World][c-hello-world]
- [GCC Install][gcc-install]
- [AWS CLI][aws-cli]
- [Azure CLI][az-cli]

<!-- References -->

[aws-cli]: https://docs.aws.amazon.com/cli/latest/userguide/cli-chap-getting-started.html
[az-cli]: https://learn.microsoft.com/en-us/cli/azure/get-started-with-azure-cli
[c-hello-world]: https://stackoverflow.com/questions/12355758/proper-hello-world-in-c
[docker-alpine]: https://hub.docker.com/_/alpine
[docker-scratch]: https://hub.docker.com/_/scratch
[gcc-install]: https://gcc.gnu.org/install/
