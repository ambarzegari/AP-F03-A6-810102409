#include "UTaste.hpp"

UTaste::UTaste()
{
    user = nullptr;
}

void UTaste::GetDataFromResturantsFile(char argv[])
{
    ifstream ResturantsFile(argv);
    string line, word;
    getline(ResturantsFile, line);

    while (getline(ResturantsFile, line))
    {
        stringstream X(line);
        string word;
        string name, dist, menu;
        int op_t, cl_t, num;
        District *dist_ptr;

        for (int i = 1; getline(X, word, ','); i++)
        {
            if (i == 1)
            {
                name = word;
            }
            if (i == 2)
            {
                dist = word;

                for (auto ptr : districts)
                {
                    if (ptr->GetName() == dist)
                    {
                        dist_ptr = ptr;
                    }
                }
            }
            if (i == 3)
            {
                menu = word;
            }
            if (i == 4)
            {
                op_t = stoi(word);
            }
            if (i == 5)
            {
                cl_t = stoi(word);
            }
            if (i == 6)
            {
                num = stoi(word);
            }
        }
        dist_ptr->AddResturant(name, menu, op_t, cl_t, num);
    }
}

void UTaste::GetDataFromDistrictsFile(char argv[])
{
    ifstream ResturantsFile(argv);
    string line, word;
    District *dist_ptr;
    getline(ResturantsFile, line);

    while (getline(ResturantsFile, line))
    {
        stringstream X(line);
        for (int i = 1; getline(X, word, ','); i++)
        {
            if (i == 1)
            {
                bool founded = true;
                for (auto nei : districts)
                {
                    if (nei->GetName() == word)
                    {
                        founded = false;
                        dist_ptr = nei;
                    }
                }
                if (founded)
                {
                    dist_ptr = new District(word);
                    districts.push_back(dist_ptr);
                }
            }
            if (i == 2)
            {
                stringstream Y(word);
                string neigh;
                for (int j = 1; getline(Y, neigh, ';'); j++)
                {
                    bool founded = true;
                    for (auto nei : districts)
                    {
                        if (nei->GetName() == neigh)
                        {
                            founded = false;
                            dist_ptr->AddNeighbors(nei);
                        }
                    }
                    if (founded)
                    {
                        District *new_dist = new District(neigh);
                        districts.push_back(new_dist);
                        dist_ptr->AddNeighbors(new_dist);
                    }
                }
            }
        }
    }
}

void UTaste::IoHandler()
{
    string line;
    vector<string> requests;

    while (getline(cin, line))
    {
        requests = StringSplitter(line);

        try
        {
            if (requests[0] == PUT)
            {
            }
            else if (requests[0] == GET)
            {
            }
            else if (requests[0] == DELETE)
            {
            }
            else if (requests[0] == POST)
            {
                POSTHandler(requests);
            }
            else
            {
                throw runtime_error(BAD_REQUEST);
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }

        requests.clear();
        line.clear();
    }
}

void UTaste::POSTHandler(vector<string> requests)
{
    if (requests[1] == SIGN_UP)
    {
        SignUp(requests);
    }
    else if (requests[1] == LOG_IN)
    {
        LogIn(requests);
    }
    else if (requests[1] == LOG_OUT)
    {
        LogOut(requests);
    }
    else
    {
        throw runtime_error(NOT_FOUND);
    }
}

void UTaste::SignUp(vector<string> requests)
{
    if (user != nullptr)
    {
        throw runtime_error(PERMISSION_DENIED);
    }

    for (auto user_ : app_users)
    {
        if (user_->CheckUsername(requests[5]))
        {
            throw runtime_error(BAD_REQUEST);
        }
    }

    if (requests[3] != USER_NAME || requests[5] != PASSWORD)
    {
        throw runtime_error(NOT_FOUND);
    }

    requests[4].erase(requests[4].begin());
    requests[4].erase(requests[4].end() - 1);
    requests[6].erase(requests[6].begin());
    requests[6].erase(requests[6].end() - 1);

    User *new_user = new User(requests[4], requests[6]);
    user = new_user;
    app_users.push_back(new_user);
    cout << "OK" << endl;
}

void UTaste::LogOut(vector<string> requests)
{
    if (user == nullptr)
    {
        throw runtime_error(PERMISSION_DENIED);
    }

    for (auto user_ : app_users)
    {
        if (user_ == user)
        {
            user_->ChangeStateToLoggedOut();
        }
    }
    user = nullptr;
    cout << OK << endl;
}

void UTaste::LogIn(vector<string> requests)
{
    if (user != nullptr)
    {
        throw runtime_error(PERMISSION_DENIED);
    }

    requests[4].erase(requests[4].begin());
    requests[4].erase(requests[4].end() - 1);
    requests[6].erase(requests[6].begin());
    requests[6].erase(requests[6].end() - 1);

    for (auto user_ : app_users)
    {
        if (user_->CheckUsername(requests[4]))
        {
            if (user_->CheckPassword(requests[6]))
            {
                user = user_;
                user->ChangeStateToInApp();
                cout << OK << endl;
                return;
            }
            else
            {
                throw runtime_error(PERMISSION_DENIED);
            }
        }
    }

    throw runtime_error(NOT_FOUND);
}

void UTaste::PUTHandler(vector<string> requests)
{
}
void UTaste::DELETEHandler(vector<string> requests)
{
}
void UTaste::GETHandler(vector<string> requests)
{
}