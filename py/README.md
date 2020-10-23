# py-apicaller

The python implementation of our API calls.


## Installation

We're using [poetry](https://python-poetry.org/docs/) to manage dependencies.


### Using `pipx` to install Poetry

[pipx](https://github.com/pipxproject/pipx) is used to install Python CLI applications globally while still isolating them in virtual environments. This allows for clean upgrades and uninstalls. `pipx` supports Python 3.6 and later.

```sh
pip install --user pipx
python3 -m pipx ensurepath
```

```sh
pipx install poetry
```


### Installing dependencies

To install dependencies, run the following command.

```sh
poetry install
```

## Testing

To perform all tests, run the following commmand.
```sh
make test
```
