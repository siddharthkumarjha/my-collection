import pandas as pd
if __name__ == "__main__":
    df = pd.read_csv('/home/siddharth/projects/test/data.csv')
    print(df.loc[[3,4,6]])
