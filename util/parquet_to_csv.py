import json
import os
from pathlib import Path
import pandas as pd  # conda install pandas pyarrow
from datetime import datetime

PARQUET_DIR = Path(r"../dataset/parquet")
OUTPUT_DIR = Path(r"../dataset/csv")

ls_files = os.listdir(PARQUET_DIR)

sensor_info = {
    "MQ-3": "Alcohol, Benzine, methane, Hexane, LPG, CO",
    "MQ-135": "Several gases, Air Quality, Compounds, VOC, harmful gases, flammable gases, smoke, steam, Aromatic (Ex. Ammonia (NH3), Sulfur (S), Benzene (C6H6), CO2, NOx)",
    "MQ-138": "High sensitivity to Toluene, Acetone, Alcohol, Methanol, Ethanol,Formaldehyde also hydrogen and organic gases (VOC)",
    "MQ-136": "H2S",
    "TGS2611": "Methane",
    "MG-811": "CO2",
    "MQ-137": "Ammonia",
    "MQ-5": "LPG Butane, Propane, Methane, Hydrogen and other combustible gases",
    "MQ-131": "Ozone also has sensitivity to strong oxide such as Cl2, NO2 &etc",

}

if __name__ == '__main__':
    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)
    for file in ls_files:
        df = pd.read_parquet(fr"{PARQUET_DIR}\{file}")
        col = ["MQ-3", "MQ-135", "MQ-138", "MQ-136", "TGS2611", "MG-811", "MQ-137", "MQ-5", "MQ-131", "tsm"]
        df.columns = col
        df.to_csv(fr"{OUTPUT_DIR}\{file.split('.')[0]}.csv", index=False)
