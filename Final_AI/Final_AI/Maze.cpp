#include<iostream>
#include <stack>
#include <set>
using namespace std;

#define R 10 
#define C 10 

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> pPair;

struct cell
{
    int row_parent, col_parent;
    double f, g, h;
};

bool kiemtra_vatcan(int row, int col,int A[][C])
{
    if (A[row][col] == 1)
        return true;
    else
        return false;
}

bool kiemtra_vitri(int row, int col)
{
    if ((row >= 0) && (row < R) && (col >= 0) && (col < C))
        return true;
    return false;
}

bool kiemtra_dich(int row, int col, Pair dich)
{
    if (row == dich.first && col == dich.second)
        return true;
    else
        return false;
}

void duongdi(cell A[][C], Pair dich)
{
    cout << "Duong di: ";
    int row = dich.first;
    int col = dich.second;

    stack<Pair> kq;

    while (!(A[row][col].row_parent == row && A[row][col].col_parent == col)) // không phải là nguồn
    {
        Pair temp = make_pair(row, col);
        kq.push(temp);
        int temp_row = A[row][col].row_parent;
        int temp_col = A[row][col].col_parent;
        row = temp_row;
        col = temp_col;
    }
    kq.push(make_pair(row, col));
    while (!kq.empty())
    {
        pair<int, int> p = kq.top();
        kq.pop();
        cout << "-> " << "(" << p.first << ", " << p.second << ")";
    }
    //return;
}

double tinhgiatriH(int row, int col, Pair dich)
{
    double temp = ((double)sqrt(pow((row - dich.first), 2) + pow((col - dich.second), 2)));
    return temp;
}

void aStarSearch(Pair nguon, Pair dich, int A[][C])
{
    if (kiemtra_vitri(nguon.first, nguon.second) == false)
    {
        cout << "Vi tri nguon khong hop le!" << endl;
        return;
    }

    if (kiemtra_vitri(dich.first, dich.second) == false)
    {
        cout << "Vi tri dich khong hop le!" << endl;
        return;
    }

    if (kiemtra_vatcan(nguon.first, nguon.second, A) == false)
    {
        cout << "Vi tri nguon la vat can!" << endl;
    }

    if (kiemtra_vatcan(dich.first, dich.second, A) == false)
    {
        cout << "Vi tri dich la vat can!" << endl;
    }

    if (kiemtra_dich(nguon.first, nguon.second, dich) == true)
    {
        cout << "Vi tri nguon va vi tri dich bi trung!" << endl;
        return;
    }

    bool daduyet[R][C];
    memset(daduyet, false, sizeof(daduyet));  // gán tất cả mảng bằng false

    cell B[R][C];
    int i, j;

    // Khởi tạo các giá trị để chuẩn bị duyệt
    for (i = 0; i < R; i++)
    {
        for (j = 0; j < C; j++)
        {
            B[i][j].f = FLT_MAX;
            B[i][j].g = FLT_MAX;
            B[i][j].h = FLT_MAX;
            B[i][j].row_parent = -1;
            B[i][j].col_parent = -1;
        }
    }

    // Khởi tạo các giá trị cho vị trí nguồn
    i = nguon.first,
    j = nguon.second;
    B[i][j].f = 0.0;
    B[i][j].g = 0.0;
    B[i][j].h = 0.0;
    B[i][j].row_parent = i;
    B[i][j].col_parent = j;

    set<pPair> chuaduyet;
    double a = 0.0;
    Pair b = make_pair(i, j);
    pPair c = make_pair(a, b);
    chuaduyet.insert(c);

    bool timthaydich = false;       // chưa tìm thấy đích

    while (!chuaduyet.empty())
    {
        pPair p = *chuaduyet.begin();       // lấy ra
        chuaduyet.erase(chuaduyet.begin()); // xoá đi phần tử vừa lấy ra

        i = p.second.first;
        j = p.second.second;
        daduyet[i][j] = true;

        double g2, h2, f2;

        //Đi lên
        if (kiemtra_vitri(i - 1, j) == true)
        {
            if (kiemtra_dich(i - 1, j, dich) == true)
            {
                B[i - 1][j].row_parent = i;
                B[i - 1][j].col_parent = j;
                cout << "Da tim thay dich!" << endl;
                duongdi(B, dich);
                timthaydich = true;
                return;
            }
            else if ( daduyet[i - 1][j] == false && kiemtra_vatcan(i - 1, j, A) == true) // nếu chưa duyệt và k phải là vật cản
            {
                // cập nhật lại các giá trị
                g2 = B[i][j].g + 1.0;
                h2 = tinhgiatriH(i - 1, j, dich);
                f2 = g2 + h2;

                if (B[i - 1][j].f == FLT_MAX || B[i - 1][j].f > f2)
                {
                    chuaduyet.insert(make_pair(f2, make_pair(i - 1, j)));

                    B[i - 1][j].f = f2;
                    B[i - 1][j].g = g2;
                    B[i - 1][j].h = h2;
                    B[i - 1][j].row_parent = i;
                    B[i - 1][j].col_parent = j;
                }
            }
        }

        // Đi xuống
        if (kiemtra_vitri(i + 1, j) == true)
        {
            if (kiemtra_dich(i + 1, j, dich) == true)
            {
                B[i + 1][j].row_parent = i;
                B[i + 1][j].col_parent = j;
                cout << "Da tim thay dich!" << endl;
                duongdi(B, dich);
                timthaydich = true;
                return;
            }
            else if (daduyet[i + 1][j] == false && kiemtra_vatcan(i + 1, j, A) == true)
            {
                g2 = B[i][j].g + 1.0;
                h2 = tinhgiatriH(i + 1, j, dich);
                f2 = g2 + h2;

                if (B[i + 1][j].f == FLT_MAX || B[i + 1][j].f > f2)
                {
                    chuaduyet.insert(make_pair(f2, make_pair(i + 1, j)));

                    B[i + 1][j].f = f2;
                    B[i + 1][j].g = g2;
                    B[i + 1][j].h = h2;
                    B[i + 1][j].row_parent = i;
                    B[i + 1][j].col_parent = j;
                }
            }
        }

        // Sang phải
        if (kiemtra_vitri(i, j + 1) == true)
        {
            if (kiemtra_dich(i, j + 1, dich) == true)
            {
                B[i][j + 1].row_parent = i;
                B[i][j + 1].col_parent = j;
                cout << "Da tim thay dich!" << endl;
                duongdi(B, dich);
                timthaydich = true;
                return;
            }
            else if (daduyet[i][j + 1] == false && kiemtra_vatcan(i, j + 1, A) == true)
            {
                g2 = B[i][j].g + 1.0;
                h2 = tinhgiatriH(i, j + 1, dich);
                f2 = g2 + h2;

                if (B[i][j + 1].f == FLT_MAX || B[i][j + 1].f > f2)
                {
                    chuaduyet.insert(make_pair(f2, make_pair(i, j + 1)));

                    B[i][j + 1].f = f2;
                    B[i][j + 1].g = g2;
                    B[i][j + 1].h = h2;
                    B[i][j + 1].row_parent = i;
                    B[i][j + 1].col_parent = j;
                }
            }
        }

        // Sang trái
        if (kiemtra_vitri(i, j - 1) == true)
        {
            if (kiemtra_dich(i, j - 1, dich) == true)
            {
                B[i][j - 1].row_parent = i;
                B[i][j - 1].col_parent = j;
                cout << "Da tim thay dich!" << endl;
                duongdi(B, dich);
                timthaydich = true;
                return;
            }
            else if (daduyet[i][j - 1] == false && kiemtra_vatcan(i, j - 1, A) == true)
            {
                g2 = B[i][j].g + 1.0;
                h2 = tinhgiatriH(i, j - 1, dich);
                f2 = g2 + h2;

                if (B[i][j - 1].f == FLT_MAX || B[i][j - 1].f > f2)
                {
                    chuaduyet.insert(make_pair(f2, make_pair(i, j - 1)));

                    B[i][j - 1].f = f2;
                    B[i][j - 1].g = g2;
                    B[i][j - 1].h = h2;
                    B[i][j - 1].row_parent = i;
                    B[i][j - 1].col_parent = j;
                }
            }
        }

        // Trên bên phải
        if (kiemtra_vitri(i - 1, j + 1) == true)
        {
            if (kiemtra_dich(i - 1, j + 1, dich) == true)
            {
                B[i - 1][j + 1].row_parent = i;
                B[i - 1][j + 1].col_parent = j;
                cout << "Da tim thay dich!" << endl;
                duongdi(B, dich);
                timthaydich = true;
                return;
            }
            else if (daduyet[i - 1][j + 1] == false && kiemtra_vatcan(i - 1, j + 1, A) == true)
            {
                g2 = B[i][j].g + 1.414;
                h2 = tinhgiatriH(i - 1, j + 1, dich);
                f2 = g2 + h2;

                if (B[i - 1][j + 1].f == FLT_MAX ||
                    B[i - 1][j + 1].f > f2)
                {
                    chuaduyet.insert(make_pair(f2,
                        make_pair(i - 1, j + 1)));

                    B[i - 1][j + 1].f = f2;
                    B[i - 1][j + 1].g = g2;
                    B[i - 1][j + 1].h = h2;
                    B[i - 1][j + 1].row_parent = i;
                    B[i - 1][j + 1].col_parent = j;
                }
            }
        }

        // Trên bên trái
        if (kiemtra_vitri(i - 1, j - 1) == true)
        {
            if (kiemtra_dich(i - 1, j - 1, dich) == true)
            {
                B[i - 1][j - 1].row_parent = i;
                B[i - 1][j - 1].col_parent = j;
                cout << "Da tim thay dich!" << endl;
                duongdi(B, dich);
                timthaydich = true;
                return;
            }
            else if (daduyet[i - 1][j - 1] == false && kiemtra_vatcan(i - 1, j - 1, A) == true)
            {
                g2 = B[i][j].g + 1.414;
                h2 = tinhgiatriH(i - 1, j - 1, dich);
                f2 = g2 + h2;

                if (B[i - 1][j - 1].f == FLT_MAX || B[i - 1][j - 1].f > f2)
                {
                    chuaduyet.insert(make_pair(f2, make_pair(i - 1, j - 1)));

                    B[i - 1][j - 1].f = f2;
                    B[i - 1][j - 1].g = g2;
                    B[i - 1][j - 1].h = h2;
                    B[i - 1][j - 1].row_parent = i;
                    B[i - 1][j - 1].col_parent = j;
                }
            }
        }

        // Dưới bên phải
        if (kiemtra_vitri(i + 1, j + 1) == true)
        {
            if (kiemtra_dich(i + 1, j + 1, dich) == true)
            {
                B[i + 1][j + 1].row_parent = i;
                B[i + 1][j + 1].col_parent = j;
                cout << "Da tim thay dich!" << endl;
                duongdi(B, dich);
                timthaydich = true;
                return;
            }
            else if (daduyet[i + 1][j + 1] == false && kiemtra_vatcan(i + 1, j + 1, A) == true)
            {
                g2 = B[i][j].g + 1.414;
                h2 = tinhgiatriH(i + 1, j + 1, dich);
                f2 = g2 + h2;

                if (B[i + 1][j + 1].f == FLT_MAX || B[i + 1][j + 1].f > f2)
                {
                    chuaduyet.insert(make_pair(f2, make_pair(i + 1, j + 1)));

                    B[i + 1][j + 1].f = f2;
                    B[i + 1][j + 1].g = g2;
                    B[i + 1][j + 1].h = h2;
                    B[i + 1][j + 1].row_parent = i;
                    B[i + 1][j + 1].col_parent = j;
                }
            }
        }

        // Dưới bên trái
        if (kiemtra_vitri(i + 1, j - 1) == true)
        {
            if (kiemtra_dich(i + 1, j - 1, dich) == true)
            {
                B[i + 1][j - 1].row_parent = i;
                B[i + 1][j - 1].col_parent = j;
                cout << "Da tim thay dich!" << endl;
                duongdi(B, dich);
                timthaydich = true;
                return;
            }
            else if (daduyet[i + 1][j - 1] == false && kiemtra_vatcan(i + 1, j - 1, A) == true)
            {
                g2 = B[i][j].g + 1.414;
                h2 = tinhgiatriH(i + 1, j - 1, dich);
                f2 = g2 + h2;

                if (B[i + 1][j - 1].f == FLT_MAX || B[i + 1][j - 1].f > f2)
                {
                    chuaduyet.insert(make_pair(f2, make_pair(i + 1, j - 1)));

                    B[i + 1][j - 1].f = f2;
                    B[i + 1][j - 1].g = g2;
                    B[i + 1][j - 1].h = h2;
                    B[i + 1][j - 1].row_parent = i;
                    B[i + 1][j - 1].col_parent = j;
                }
            }
        }

    }
    if (timthaydich == false)
        cout << "Khong tim thay duong di toi dich!" << endl;
    return;
}

Pair nhapvitriNguon(int A[][C])
{
    int x, y;
    do {
        cout << "Nhap hang cua nguon: ";
        cin >> x;
        cout << "Nhap cot cua nguon: ";
        cin >> y;
    } while (kiemtra_vitri(x, y) == false || kiemtra_vatcan(x, y, A) == false);
    Pair src = make_pair(x, y);
    return src;
}

Pair nhapvitriDich(int A[][C])
{
    int x, y;
    do {
        cout << "Nhap hang cua dich: ";
        cin >> x;
        cout << "Nhap cot cua dich: ";
        cin >> y;
    } while (kiemtra_vitri(x, y) == false || kiemtra_vatcan(x, y, A) == false);
    Pair dest = make_pair(x, y);
    return dest;
}

int main()
{
    Pair nguon, dich;
    int A[R][C] =
    {
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
    };

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
            cout << A[i][j] << "  ";
        cout << endl;
    }

    nguon = nhapvitriNguon(A);
    dich = nhapvitriDich(A);
    aStarSearch(nguon, dich, A);

    return 0;
}