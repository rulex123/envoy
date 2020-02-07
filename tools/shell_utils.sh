source_venv() {
  echo "Hello source_venv"
  VENV_DIR=$1
  if [[ "${VIRTUAL_ENV}" == "" ]]; then
    if [[ ! -d "${VENV_DIR}"/venv ]]; then
      echo "creating virtual env ${VENV_DIR}"
      virtualenv "${VENV_DIR}"/venv --no-site-packages --python=python3
    fi
    source "${VENV_DIR}"/venv/bin/activate
  else
    echo "Found existing virtualenv"
  fi
}

python_venv() {
  echo "Hello python_venv"
  SCRIPT_DIR=$(realpath "$(dirname "$0")")

  BUILD_DIR=build_tools
  PY_NAME="$1"
  VENV_DIR="${BUILD_DIR}/${PY_NAME}"

  echo "VENV_DIR=${VENV_DIR}"

  source_venv "${VENV_DIR}"
  pip install -r "${SCRIPT_DIR}"/requirements.txt

  shift
  python3 "${SCRIPT_DIR}/${PY_NAME}.py" $*
}
