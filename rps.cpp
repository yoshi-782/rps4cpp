#include <iostream>
#include <stdlib.h>
//#include <ncurses.h> // Linux
#include <conio.h> // windows

#define KEY_LEFT   75
#define KEY_RIGHT  77
#define KEY_ENTER  13
#define KEY_CTRL_C  3

int result_rps(int yourps);

std::string rpc_data[3] = { "グー", "チョキ", "パー" };

int start_rps()
{
    int yourps = 0;
    std::string write = "";

    // コンソール画面クリア
    system("cls");
    std::cout << "最初はグー！じゃんけん！" << std::endl;
    std::cout << "[カーソルで選択してください]\n" << std::endl;
    std::cout << "→グー　　チョキ　　パー";

    // エンターが押されるまでループ
    while(true)
    {
        // キー入力取得
        switch (getch())
        {
            // 左入力
            case KEY_LEFT: yourps = yourps == 0 ? 2 : yourps - 1; break;
            // 右入力
            case KEY_RIGHT: yourps = yourps == 2 ? 0 : yourps + 1; break;
            // Ctrl+c
            case KEY_CTRL_C: exit(0);
            // エンター入力 (上書き解除→result_rps関数実行)
            case KEY_ENTER: std::cout << "\n" << std::endl; return result_rps(yourps);
        }

        // 選択文字作成
        for (int i = 0; i < 3; i++)
        {
            if (i == yourps)
            {
                // カーソルあり
                write = i == 0 ? write + "" : write + "　";
                write = write + "→" + rpc_data[i];
            }
            else
            {
                // カーソルなし
                write = i == 0 ? write + "　" : write + "　　";
                write = write + "" + rpc_data[i];
            }
        }

        // 選択場所上書き出力
        std::cout << "\r" << write;
        write = "";
    }
}

int result_rps(int yourps)
{
    // 乱数1～2を取得
    int r = rand() % 2 + 1;
    // 相手のじゃんけん結果出力
    std::cout << rpc_data[r] << "！" << std::endl;
    // じゃんけん式
    int result = (yourps - r + 3) % 3;
    // 勝敗出力
    switch (result)
    {
        case 0:
            std::cout << "あいこです！" << std::endl;
            return 1;
        case 1:
            std::cout << "あなたの負けです！" << std::endl;
            return 1;
        case 2:
            std::cout << "あなたの勝ちです！" << std::endl;
            return 0;
        default:
            return 0;
    }
}

int is_try_again()
{
    int rematch = 0;
    std::string yesno[2] = { "はい", "いいえ" };
    std::string write = "";
    std::cout << "再挑戦しますか？" << std::endl;
    std::cout << "→はい　　いいえ";
    while(true)
    {
        // キー入力取得
        switch (getch())
        {
            // 左入力
            case KEY_LEFT: rematch = rematch == 0 ? 1 : 0; break;
            // 右入力
            case KEY_RIGHT: rematch = rematch == 1 ? 0 : 1; break;
            // Ctrl+c
            case KEY_CTRL_C: exit(0);
            // エンター入力
            case KEY_ENTER:
                // 上書き解除
                std::cout << std::endl; 
                // コンソール画面クリア
                system("cls");
                // rematchを返す
                return rematch;
        }

        // 選択文字作成
        for (int i = 0; i < 2; i++)
        {
            if (i == rematch)
            {
                // カーソルあり
                write = i == 0 ? write + "" : write + "　";
                write = write + "→" + yesno[i];
            }
            else
            {
                // カーソルなし
                write = i == 0 ? write + "　" : write + "　　";
                write = write + "" + yesno[i];
            }
        }

        // 選択場所上書き出力
        std::cout << "\r" << write;
        write = "";
    }
}

int main()
{
    while(true)
    {
        // じゃんけん開始
        if (start_rps() == 1)
        {
            // 再挑戦チェック
            if(is_try_again() == 1)
            {
                // いいえを選択したので処理を抜ける 
                break;
            }
        }
        else
        {
            // 勝ったので処理を抜ける
            break;
        }
    }

    return 0;
}
