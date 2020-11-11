#!/bin/bash
set -x

function main {

  init_params "$@"
  run_tuning

}

# init params
function init_params {

  for var in "$@"
  do
    case $var in
      --topology=*)
          topology=$(echo $var |cut -f2 -d=)
      ;;
      --dataset_location=*)
          dataset_location=$(echo $var |cut -f2 -d=)
      ;;
      --input_model=*)
          input_model=$(echo $var |cut -f2 -d=)
      ;;
      --output_model=*)
          output_model=$(echo $var |cut -f2 -d=)
      ;;
      *)
          echo "Error: No such parameter: ${var}"
          exit 1
      ;;
    esac
  done

}

# run_tuning
function run_tuning {
    sed -i "s|/path/to/calibration/dataset|$dataset_location/train|g" conf.yaml
    sed -i "s|/path/to/evaluation/dataset|$dataset_location/val|g" conf.yaml
    python setup.py install
    extra_cmd="${dataset_location}"

    python examples/imagenet_eval.py \
            --data ${extra_cmd} \
            -a $topology \
            -b 128 \
            -j 1 \
            -t

}

main "$@"
