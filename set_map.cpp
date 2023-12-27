#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
// 3 set
/*
int FindLongestQueOfDifferentNumbers(const std::vector<int> vec) {
  int left = 0;
  int right = 0;
  int longest = 0;
  int count = 0;
  std::set<int> s;
  while (right < vec.size()) {
    if (s.find(vec[right]) == s.end()) {
      s.insert(vec[right]);
      ++count;
      ++right;

    } else {
      s.erase(vec[left]);
      ++left;
      --count;
    }
    if (count > longest) {
      longest = count;
    }
  }
}
*/

// 6 map
/*
bool startsWith(const std::string &prefix) {
  TrieNode *curren = root;
  for (char ch : prefix) {
    if (curren->children.find(ch) == curren->children.end())
      return false;
    curren = curren->children[ch];
  }
  return true;
}
*/
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};
// 7
int SumOfPath(TreeNode *root, std::map<int, int> &m) {
  if (root == nullptr)
    return 0;
  int left_sum = SumOfPath(root->left, m);
  int right_sum = SumOfPath(root->right, m);
  int sum = left_sum + right_sum + root->val;
  m[sum]++;
  return sum;
}
std::vector<int> findFrequentTreeSum(TreeNode *root) {
  std::map<int, int> mp;
  std::vector<int> res;
  SumOfPath(root, mp);
  int max = -1;
  for (auto it = mp.begin(); it != mp.end(); ++it) {
    if (it->second > max)
      max = it->second;
  }
  for (auto it = mp.begin(); it != mp.end(); ++it) {
    if (it->second == max)
      res.push_back(it->first);
  }
  return res;
}

int main() {
  // 1 set
  /*
  std::set<int> st;
  int n;
  std::cin >> n;
  int numb;
  while(n--)
  {
    std::cin>>numb;
    st.insert(numb);
  }
  std::cout << st.size() << std::endl;
  */
  // 2 set
  /*
  std::string jevs_and_stones;
  std::set<char>jevels;
  std::cin>>jevs_and_stones;
  for(char ch: jevs_and_stones)
    jevels.insert(ch);
  std::cin>>jevs_and_stones;
  std::vector<char>stones;
  for(char ch: jevs_and_stones)
    stones.push_back(ch);
  int ans = 0;
  for(auto it = stones.begin(); it!= stones.end(); ++it)
  {
    if(jevels.find(*it)!=jevels.end())
      ++ans;
  }
  std::cout<<ans;
  */

  // 1 map
  /*
  std::string str;
  std::cin>>str;
  std::map<char, int> mp;
  int min = str.size();
  for(std::size_t i = 0; i < str.size(); ++i)
  {
    if(mp.count(str[i]))
      mp[str[i]] = -1;
    else
      mp[str[i]]=i;
  }
  for(auto it = mp.begin(); it!= mp.end(); ++it)
    {
      if(it->second != -1)
        min = std::min(min, it->second);
    }
  if(min == str.size())
    std::cout<<-1<<std::endl;
  else
    std::cout<<min<<std::endl;
  */
  // 2 map
  /*
  std::string str;
  std::cin >> str;
  std::map<char, int> mp;
  for (std::size_t i = 0; i < str.size(); ++i)
    mp[str[i]]++;
  int result = 0;
  bool is_there_odd
  for (auto it = mp.begin(); it != mp.end(); ++it) {
    if (it->second % 2 == 0)
      result += it->second; // zuygery misht karelia avelacnel palindrom
    else{
      result += it->second -1; kara lini
      is_there_odd = true;
      }
  }
  if(is_there_odd)
     result++;
  std::cout << result;
  */
  // 3 map
  /*
  std::vector<int> numbers;
  int numb;
  std::cin >> numb;
  while (numb--)
  {
    int n;
    std::cin >> n;
    numbers.push_back(n);
  }
  std::cin>> numb;
  std::map<int, int> mp;
  bool ans = false;
  for(std::size_t i =0; i<numbers.size(); ++i)
  {
    if(mp.count(numbers[i]))
    {
      if(i - mp[numbers[i]] <= numb)
      {
        ans = true;
        break;
      }
      else
        mp[numbers[i]] = i;
    }
    else
      mp[numbers[i]] = i;
  }
  std::cout<<std::boolalpha<<ans<<std::endl;
  */
  // 4 map
  /*
  std::string pattern;
  std::cin >> pattern;
  std::cin >> std::ws;
  std::cout << "enter text \n";
  std::string text;
  std::getline(std::cin, text);
  std::map<char, std::string> mp;
  std::istringstream iss(text);
  std::string part;
  for (char ch : pattern) {
    iss >> part;
    mp[ch] = part;
  }
  std::istringstream oss(text);
  bool ans = true;
  for (char ch : pattern) {
    oss >> part;
    if (mp[ch] != part)
      ans = false;
  }
  std::cout << std::boolalpha << ans << std::endl;
*/
  // 5 map
  /*
    std::string characters;
  std::cin >> characters;
  std::map<char, int> mp;
  for (char ch : characters)
    mp[ch]++;
  std::vector<std::pair<char,int>> vec;
  for (auto it = mp.begin(); it != mp.end(); ++it)
      vec.push_back(std::make_pair(it->first, it->second));
  std::sort(vec.begin(), vec.end(), [](const std::pair<char,int>& lhs, const
  std::pair<char,int>& rhs){ return lhs.second > rhs.second;
  });
  for(std::size_t i = 0; i < vec.size(); ++i)
  {
    for(std::size_t j = 0; j < vec[i].second; ++j)
      std::cout<<vec[i].first;
  }
  */

  // 7
  TreeNode tree{5, new TreeNode(2), new TreeNode(-5)};
  std::vector<int> res = findFrequentTreeSum(&tree);
  for (auto it : res) {
    std::cout << it << " ";
  }

  return 0;
}
