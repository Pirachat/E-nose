import json
import os
from  pathlib  import Path
import pandas as pd  # conda install pandas pyarrow
from datetime import datetime

RAW_DIR = Path(r"../dataset/raw/raw_data_air")
RAW_FILE = "raw_data_air_5_2022_01_31T050832.json"
CURATED_DIR = Path(r"../dataset/parquet")

MAX_SENSOR = 9

# Create empty DataFrame with specific column types
df = pd.DataFrame({'tsm_ns': pd.Series(dtype='int'),
                   's1': pd.Series(dtype='int'),
                   's2': pd.Series(dtype='int'),
                   's3': pd.Series(dtype='int'),
                   's4': pd.Series(dtype='int'),
                   's5': pd.Series(dtype='int'),
                   's6': pd.Series(dtype='int'),
                   's7': pd.Series(dtype='int'),
                   's8': pd.Series(dtype='int'),
                   's9': pd.Series(dtype='int'),
                   })

if __name__ == '__main__':
    with open(os.path.join(RAW_DIR, RAW_FILE), 'r') as f:
        lines = f.readlines()
        for line in lines:
            try:
                a_json = json.loads(line)
                # print(a_json)
                # if "sensors" not in [a_json.keys()]:
                #     continue
                # transform to dataframe

                a_json['sensors'] = json.loads(a_json['sensors'])
                if len(a_json['sensors']['data']) != MAX_SENSOR:
                    continue
                new_row = {
                    "tsm_ns": a_json['tsm_ns'],
                    "s1": a_json['sensors']['data'][0],
                    "s2": a_json['sensors']['data'][1],
                    "s3": a_json['sensors']['data'][2],
                    "s4": a_json['sensors']['data'][3],
                    "s5": a_json['sensors']['data'][4],
                    "s6": a_json['sensors']['data'][5],
                    "s7": a_json['sensors']['data'][6],
                    "s8": a_json['sensors']['data'][7],
                    "s9": a_json['sensors']['data'][8]
                }
                df = df.append(new_row, ignore_index=True)

            except json.decoder.JSONDecodeError:
                print("String could not be converted to JSON")
    df['tsm2'] = pd.to_datetime(df['tsm_ns'] / 1000000, unit='ms', ).astype('datetime64[ms]')
    print(df.dtypes)
    print(df)

    pass

    df.drop(columns=['tsm_ns'], inplace=True)
    df.rename(columns={'tsm2': 'tsm'}, inplace=True)
    filename, file_extension = os.path.splitext(RAW_FILE)
    CURATED_FILE = f'curated_{filename}.snappy.parquet'
    if not os.path.exists(CURATED_DIR):
        os.makedirs(CURATED_DIR)
    output_fullname = os.path.join(CURATED_DIR, CURATED_FILE)
    print("Output file: ",output_fullname)
    df.to_parquet(output_fullname)
