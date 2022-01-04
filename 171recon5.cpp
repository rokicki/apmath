#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <sys/time.h>
using namespace std ;
vector<vector<vector<int>>> alljw(
 {{{1, 6, 14, 36, 46, 76, 173, 181, 196, 216, 261}, 
  {17, 37, 43, 53, 59, 79, 97, 102, 269, 274}, {32, 52, 62, 83, 84, 94, 178, 
   191, 192, 199, 213, 222, 223, 229, 232, 238, 239, 243, 258}, 
  {2, 12, 13, 20, 34, 44, 50, 60, 64, 82, 90, 95, 110, 113, 128, 132, 133, 
   139, 142, 148, 149, 155, 158, 172, 175, 179, 180, 190, 193, 198}}, 
 {{1, 6, 14, 36, 46, 76, 181, 191, 196, 216, 261}, 
  {17, 37, 43, 53, 59, 79, 97, 102, 269, 274}, {32, 52, 62, 83, 84, 94, 173, 
   178, 192, 199, 213, 222, 223, 229, 232, 238, 239, 243, 258}, 
  {2, 12, 13, 20, 34, 44, 50, 60, 64, 82, 90, 95, 110, 113, 128, 132, 133, 
   139, 142, 148, 149, 155, 158, 172, 175, 179, 180, 190, 193, 198}}, 
 {{1, 6, 17, 36, 46, 76, 181, 191, 196, 216, 261}, 
  {37, 53, 79, 232, 258, 274}, {14, 32, 43, 52, 59, 62, 83, 84, 94, 97, 102, 
   173, 178, 192, 199, 213, 222, 223, 229, 238, 239, 243, 269}, 
  {0, 4, 19, 22, 30, 35, 42, 50, 68, 72, 73, 82, 88, 89, 95, 98, 112, 115, 
   119, 120, 130, 133, 138, 209, 214, 217, 227, 228, 235, 249, 252, 259, 265, 
   268}},
  {{1, 6, 36, 43, 46, 76, 181, 191, 196, 216, 261}, 
  {17, 32, 37, 94, 222, 239}, {14, 52, 53, 59, 62, 79, 83, 84, 97, 102, 173, 
   178, 192, 199, 213, 223, 229, 232, 238, 243, 258, 269, 274}, 
  {4, 8, 13, 28, 38, 65, 67, 73, 77, 78, 95, 99, 105, 107, 134, 135, 140, 
   144, 155, 159, 164, 168, 179, 198, 200, 208, 212, 220, 225, 227, 235, 247, 
   249, 268}}}) ;
/*
 *   Reconstitute a solution.
 */
long long rescnts[30000] ;
int n, xinc, yinc ;
int seq ;
int base[3][3][275][2] ;
int xoff[3][3][275], yoff[3][3][275] ;
int tempw[2475], temph[2475], tempb[2475], tempm[2475] ;
vector<pair<int, int>> pts[3][3][275] ;
map<vector<pair<int, int>>, int> seen ;
vector<vector<vector<int>>> seqex ;
vector<vector<vector<char>>> bitmaps ;
int main(int argc, char *argv[]) {
   srand48(time(0)) ;
   n = atol(argv[1]) ;
   xinc = atol(argv[2]) ;
   yinc = atol(argv[3]) ;
   int best = 1000000000 ;
   int besti = -1 ;
   int bestj = -1 ;
   for (int i=3; i<1000; i += 3) {
      if (i * i >= best)
         break ;
      for (int j=3; j<1000; j += 3) {
         if (i * i + j * j >= best)
            break ;
         if ((xinc * i + yinc * j) % 275 != 0)
            continue ;
         best = i * i + j * j ;
         besti = i ;
         bestj = j ;
      }
   }
   int firsti = besti ;
   int firstj = bestj ;
   best = 1000000000 ;
   besti = -1 ;
   bestj = -1 ;
   for (int i=3; i<1000; i += 3) {
      if (i * i >= best)
         break ;
      for (int j=3; j<1000; j += 3) {
         if (i * i + j * j >= best)
            break ;
         if ((xinc * (275 - i % 275) + yinc * j) % 275 != 0)
            continue ;
         best = i * i + j * j ;
         besti = -i ;
         bestj = j ;
      }
   }
   int fourthi = besti ;
   int fourthj = bestj ;
   int w = 2 * n - 1 ;
   int det = firstj * fourthi - firsti * fourthj ;
   for (int a=0; a<3; a++)
      for (int b=0; b<3; b++)
         for (int c=0; c<275; c++)
            base[a][b][c][0] = -1 ;
   for (int i=0; i<w; i++) {
      for (int j=0; j<w; j++) {
         if (j - i >= n)
            break ;
         if (i - j < n) {
            int a = i % 3 ;
            int b = j % 3 ;
            int c = (i * xinc + j * yinc) % 275 ;
            if (base[a][b][c][0] != -1) {
               int hexx = j - base[a][b][c][1] ;
               int hexy = i - base[a][b][c][0] ;
               int xnum = (hexx * fourthi - hexy * fourthj) ;
               int ynum = (firstj * hexy - firsti * hexx) ;
               if (xnum % det != 0 || ynum % det != 0) {
                  cout << "Fail in calculation" << endl ;
                  exit(0) ;
               }
               xnum /= det ;
               ynum /= det ;
               pts[a][b][c].push_back({xnum, ynum}) ;
            } else {
               base[a][b][c][0] = i ;
               base[a][b][c][1] = j ;
               pts[a][b][c].push_back({0, 0}) ;
            }
         }
      }
   }
   vector<int> mapv ;
   for (int a=0; a<3; a++) {
      for (int b=0; b<3; b++) {
         for (int c=0; c<275; c++) {
            int minx = 0 ;
            int miny = 0 ;
            for (auto pt: pts[a][b][c]) {
               minx = min(pt.first, minx) ;
               miny = min(pt.second, miny) ;
            }
            int maxx = 0 ;
            int maxy = 0 ;
            for (auto &pt: pts[a][b][c]) {
               pt.first -= minx ;
               pt.second -= miny ;
               maxx = max(pt.first, maxx) ;
               maxy = max(pt.second, maxy) ;
            }
            if (maxx == 0 && maxy == 0) {
               cout << "Broken" << endl ;
               exit(0) ;
            }
            if (seen.find(pts[a][b][c]) == seen.end()) {
               tempw[seq] = maxx + 1 ;
               temph[seq] = maxy + 1 ;
               tempm[seq] = tempw[seq] * 2 ;
               int bv = 0 ;
               for (auto &pt: pts[a][b][c])
                  bv = max(bv, pt.first + pt.second * tempm[seq]) ;
               tempb[seq] = bv ;
               seen[pts[a][b][c]] = seq++ ;
               vector<vector<char>> bm(maxy+1) ;
               for (auto &v: bm)
                  v.resize(maxx+1) ;
               for (auto &pt: pts[a][b][c])
                  bm[pt.second][pt.first] = 1 ;
               bitmaps.push_back(bm) ;
            }
            mapv.push_back(seen[pts[a][b][c]]) ;
            xoff[a][b][c] = minx ;
            yoff[a][b][c] = miny ;
         }
      }
   }
   int v ;
   int seq2 = 0 ;
   vector<int> solv ;
   vector<vector<int>> sols ;
   vector<vector<vector<int>>> xsols ;
   ifstream solf(argv[4]) ;
   string s ;
   sols.resize(seq) ;
   xsols.resize(seq) ;
   solv.resize(seq) ;
   while (getline(solf, s)) {
      vector<int> sol ;
      istringstream is(s) ;
      while (is >> v)
         sol.push_back(v) ;
      if (sol.size() == 0) {
         seq2++ ;
      } else {
         sol[0] -= tempb[seq2] ;
         for (int i=1; i<(int)sol.size(); i++)
            sol[i] += sol[i-1] ;
         sols[seq2] = sol ;
         xsols[seq2].push_back(sol) ;
         solv[seq2] = sol.size() ;
      }
   }
   solf.close() ;
   if (seq != seq2)
      cout << "Out of sync in solutions " << seq << " " << seq2 << endl ;
   // do any of the existing solutions improve any other solutions?
   vector<int> tmpsol ;
   vector<vector<vector<int>>> ysols(seq) ;
   for (int ii=0; ii<(int)xsols.size(); ii++) {
      auto &oldsol = xsols[ii] ;
      for (int i=0; i<(int)oldsol.size(); i++) {
         for (int j=0; j<seq; j++) {
            if ((int)oldsol[i].size() >= solv[j]) {
               for (int dx=-1; dx<=1; dx++) {
                  for (int dy=-1; dy<=1; dy++) {
                     for (int pass=0; pass<2; pass++) {
                        tmpsol.clear() ;
                        int cnt = 0 ;
                        for (auto v: oldsol[i]) {
                           int x = dx + v % tempm[ii] ;
                           int y = dy + v / tempm[ii] ;
                           if (x >= 0 && x < tempw[j] && y >= 0 && y < temph[j] && bitmaps[j][y][x]) {
                              if (pass == 0) {
                                 cnt++ ;
                              } else {
                                 tmpsol.push_back(x + tempm[j] * y) ;
                              }
                           }
                        }
                        if (pass == 0) {
                           if (cnt < solv[j])
                              break ;
                        } else {
                           if ((int)tmpsol.size() > solv[j])
                              ysols[j].clear() ;
                           ysols[j].push_back(tmpsol) ;
                           solv[j] = tmpsol.size() ;
                           sols[j] = tmpsol ;
                        }
                     }
                  }
               }
            }
         }
      }
   }
   for (int i=0; i<(int)ysols.size(); i++) {
      set<vector<int>> good ;
      for (auto v: ysols[i])
         good.insert(v) ;
      ysols[i].clear() ;
      for (auto v: good)
         ysols[i].push_back(v) ;
   }
   vector<pair<int, vector<int>>> allr ;
   int solvmapv[2475] ;
   for (int i=0; i<2475; i++)
      solvmapv[i] = solv[mapv[i]] ;
   for (int seq=0; seq<(int)alljw.size(); seq++) {
      auto &jw = alljw[seq] ;
      vector<vector<int>> a ;
      for (int i=0; i<(int)jw[0].size(); i++) {
         a.push_back({0, 0, jw[0][i]}) ;
         a.push_back({0, 1, jw[0][i]}) ;
         a.push_back({1, 0, jw[0][i]}) ;
         a.push_back({1, 1, jw[0][i]}) ;
      }
      for (int i=0; i<(int)jw[1].size(); i++) {
         a.push_back({0, 0, jw[1][i]}) ;
         a.push_back({1, 0, jw[1][i]}) ;
         a.push_back({2, 1, jw[1][i]}) ;
         a.push_back({2, 2, jw[1][i]}) ;
      }
      for (int i=0; i<(int)jw[2].size(); i++) {
         a.push_back({0, 0, jw[2][i]}) ;
         a.push_back({1, 0, jw[2][i]}) ;
         a.push_back({2, 2, jw[2][i]}) ;
      }
      for (int i=0; i<(int)jw[3].size(); i++) {
         a.push_back({2, 1, jw[3][i]}) ;
      }
      seqex.push_back(a) ;
      for (int m1=1; m1<2; m1++) {
         for (int m2=1; m2<3; m2++) {
            for (int m3=1; m3<275; m3++) {
               if (m3 % 5 == 0 || m3 % 11 == 0)
                  continue ;
               for (int a1=0; a1<3; a1++) {
                  for (int a2=0; a2<3; a2++) {
                     int tot[275] ;
                     for (int a3=0; a3<275; a3++)
                        tot[a3] = 0 ;
                     for (auto c: a) {
                        int c1 = (c[0] * m1 + a1) % 3 ;
                        int c2 = (c[1] * m2 + a2) % 3 ;
                        int c3 = (c[2] * m3) % 275 ;
                        int co = 275 * (c2 + 3 * c1) ;
                        int a3 = 0 ;
                        for (int i=c3; i<275; i++, a3++)
                           tot[a3] += solvmapv[i+co] ;
                        for (int i=0; i<c3; i++, a3++)
                           tot[a3] += solvmapv[i+co] ;
                     }
                     for (int i=0; i<275; i++)
                        allr.push_back({-tot[i], {seq, m1, m2, m3, a1, a2, i}}) ;
                  }
               }
            }
         }
      }
   }
   sort(allr.begin(), allr.end()) ;
   while (1) {
      int p = 1 ;
      while (p < (int)allr.size() && allr[0].first == allr[p].first)
         p++ ;
      p = (int)(p*drand48()) ;
      auto sol = allr[p] ;
      int bestseq = sol.second[0] ;
      int bestm1 = sol.second[1] ;
      int bestm2 = sol.second[2] ;
      int bestm3 = sol.second[3] ;
      int besta1 = sol.second[4] ;
      int besta2 = sol.second[5] ;
      int besta3 = sol.second[6] ;
      vector<int> r ;
      auto &a = seqex[bestseq] ;
      int hexm = 2 * w ;
      int hexb = (hexm + 1) * (w - 1) ;
      for (auto cc: a) {
         int a = (cc[0] * bestm1 + besta1) % 3 ;
         int b = (cc[1] * bestm2 + besta2) % 3 ;
         int c = (cc[2] * bestm3 + besta3) % 275 ;
         int seq = mapv[c + 275 * (b + 3 * a)] ;
         int xadd = xoff[a][b][c] ;
         int yadd = yoff[a][b][c] ;
         auto &tsol = ysols[seq][(int)(ysols[seq].size()*drand48())] ;
         for (auto v: tsol) {
            int x = v % tempm[seq] + xadd ;
            int y = v / tempm[seq] + yadd ;
            int hexx = x * firstj + y * fourthj + base[a][b][c][1] ;
            int hexy = x * firsti + y * fourthi + base[a][b][c][0] ;
            r.push_back(hexb + hexx + hexy * hexm) ;
         }
      }
      sort(r.begin(), r.end()) ;
      for (int i=(int)r.size()-1; i>0; i--)
         r[i] -= r[i-1] ;
      for (auto v: r)
         cout << " " << v ;
      cout << endl ;
   }
}
