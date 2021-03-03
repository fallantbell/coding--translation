# coding--translation  
## 前情提要  
我原本在筆記型電鬧上創作了一個植物大戰殭屍的小遊戲  
後來想把它移到我的桌機上  
卻發現裡面的中文都變成了亂碼  
### 正常的程式碼  
![image](https://github.com/fallantbell/coding--translation/blob/main/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202021-03-02%20224025.png)  

### 有亂碼的程式碼  
![image](https://github.com/fallantbell/coding--translation/blob/main/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202021-03-02%20224043.png)  

研究一下發現原來我筆電上面的是ANSI編碼  
可是我桌機上卻是UTF8  
所以要想完整的怡過去  
就要把所有的檔案重新編碼  
但是檔案太多 實在過於麻煩  
所以身為資工系 我決定寫可以一個自動把所有檔案從ANSI轉換到UTF8的程式  

## 功能
1 列出指定資料夾下的所有檔案  
2 轉換指定檔案的編碼  
使用要先修改程式裡面的dir 為資料夾的絕對路徑
