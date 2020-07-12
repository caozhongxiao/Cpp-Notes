[TOC]

[50道SQL经典面试题(上)](https://mp.weixin.qq.com/s?__biz=MzA3MTg4NjY4Mw==&mid=2457307221&idx=1&sn=02e16948ce3bc70b60be953406c635c8&chksm=88a59a61bfd213770cbfda4b0610f27ff4f92998ee0f1ab45b3a209abdc27e98efe64ee52e6a&scene=21#wechat_redirect)     [50道SQL经典面试题(下)](https://mp.weixin.qq.com/s/VYebTD2KjoKWQ2U4Oth6iA)

[我的博客整理：34道](https://blog.csdn.net/kernelxiao/article/details/107062487)

# 数据准备

**一、表结构**

1、学生表

Student(Sid, Sname, Sage, Ssex) 

学生编号，学生姓名，出生年月，学生性别



2、课程表

Course(Cid, Cname, Tid) 

课程编号，课程名称，教师编号



3、教师表

Teacher(Tid, Tname)

教师编号，教师姓名



4、成绩表

SC(Sid, Cid, Score)

学生编号，课程编号，分数



**二、表之间的关系**

四张表之间的关系如下图：

![image-20200712144942296](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20200712144942296.png)

关系解读：

1、课程表Course的课程编号(Cid)作为主键，在成绩表(SC)中可以看到一个或多个学生的课程分数，两表之间是属于1：n的关系。同理学生表(Student)与成绩表(SC)也是1：n的关系。

2、教师表Teacher的教师编号(Tid)作为主键，在课程表(Course)中可以带一门或多门课程，两表之间也是属于1：n的关系。

```mysql
# 添加/删除主键
# 建表时添加
create table tableName(
	id int primary key
);
或：
create table tableName(
	id int,
	primary key (id)
);
# 单独添加
alter table tableName add primary key(id)
# 删除主键
alter table tableName drop primary key;
```



**三、测试数据**

建立如下四张表：

![image-20200701141736813](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20200701141736813.png)



1、学生表

```mysql
# 建表语句
CREATE TABLE Student (
  SID VARCHAR (10),
  Sname nvarchar (10),
  Sage datetime,
  Ssex nvarchar (10)
)
#注：char，varchar，nvarchar都用来存储字符串，方式不同。
#频繁改变的字段应该用char，因为每次修改varchar都会重新计算长度，而这些char不用。
#大数据量（多行）提取时varchar的磁盘I/O消耗更低，意味着varchar在综合查询性能上比char更好。
#建议纯英文和数字用char/varchar，有中文使用nvarchar。

# 插入测试数据
INSERT INTO Student VALUES('01' , N'赵雷' , '1990-01-01' , N'男')
INSERT INTO Student VALUES('02' , N'钱电' , '1990-12-21' , N'男')
INSERT INTO Student VALUES('03' , N'孙风' , '1990-05-20' , N'男')
INSERT INTO Student VALUES('04' , N'李云' , '1990-08-06' , N'男')
INSERT INTO Student VALUES('05' , N'周梅' , '1991-12-01' , N'女')
INSERT INTO Student VALUES('06' , N'吴兰' , '1992-03-01' , N'女')
INSERT INTO Student VALUES('07' , N'郑竹' , '1989-07-01' , N'女')
INSERT INTO Student VALUES('08' , N'王菊' , '1990-01-20' , N'女')
```

结果如下：

![image-20200701131125004](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20200701131125004.png)



2、课程表

```mysql
# 建表语句
CREATE TABLE Course (
  CID VARCHAR (10),
  Cname nvarchar (10),
  TID VARCHAR (10)
)
# 插入测试数据
INSERT INTO Course VALUES('01' , N'语文' , '02')
INSERT INTO Course VALUES('02' , N'数学' , '01')
INSERT INTO Course VALUES('03' , N'英语' , '03')
```

结果如下：

![image-20200701131504781](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20200701131504781.png)



3、教师表

```mysql
# 建表语句
CREATE TABLE Teacher (
  TID VARCHAR (10),
  Tname nvarchar (10)
)
# 插入测试数据
INSERT INTO Teacher VALUES('01' , N'张三')
INSERT INTO Teacher VALUES('02' , N'李四')
INSERT INTO Teacher VALUES('03' , N'王五')
```

结果如下：

![image-20200701131753339](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20200701131753339.png)



4、成绩表

```mysql
# 建表语句
CREATE TABLE SC (
  SID VARCHAR (10),
  CID VARCHAR (10),
  score DECIMAL (18, 1)
)
#注：DECIMAL数据类型用于在数据库中存储精确的数值。语法：DECIMAL(P, D)
#P是表示有效数字数的精度。P范围为1〜65，默认是10。D是表示小数点后的位数。D的范围是0~30。
#MySQL要求D小于或等于(<=)P。
#eg. amount DECIMAL(6,2);
#在此示例中，amount列最多可以存储6位数字，小数位数为2位; 因此，amount列的范围是从-9999.99到9999.99。

# 插入测试数据
INSERT INTO SC VALUES('01' , '01' , 80)
INSERT INTO SC VALUES('01' , '02' , 90)
INSERT INTO SC VALUES('01' , '03' , 99)
INSERT INTO SC VALUES('02' , '01' , 70)
INSERT INTO SC VALUES('02' , '02' , 60)
INSERT INTO SC VALUES('02' , '03' , 80)
INSERT INTO SC VALUES('03' , '01' , 80)
INSERT INTO SC VALUES('03' , '02' , 80)
INSERT INTO SC VALUES('03' , '03' , 80)
INSERT INTO SC VALUES('04' , '01' , 50)
INSERT INTO SC VALUES('04' , '02' , 30)
INSERT INTO SC VALUES('04' , '03' , 20)
INSERT INTO SC VALUES('05' , '01' , 76)
INSERT INTO SC VALUES('05' , '02' , 87)
INSERT INTO SC VALUES('06' , '01' , 31)
INSERT INTO SC VALUES('06' , '03' , 34)
INSERT INTO SC VALUES('07' , '02' , 89)
INSERT INTO SC VALUES('07' , '03' , 98)
```

结果如下：

![image-20200701141710588](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20200701141710588.png)



# 面试题

#### 1 ~ 25

1、查询" 01 "课程比" 02 "课程成绩高的学生的信息及课程分数

```mysql
# 方法一
SELECT  a.*, b.score
FROM  Student a
JOIN SC b ON a.SID = b.SID
JOIN sc c ON b.SID = c.SID
WHERE  b.Cid = '01'
AND c.Cid = '02'
AND b.Score > c.Score

# 方法二
SELECT a.*, b.score
FROM student a
JOIN
(SELECT * FROM sc WHERE Cid = '01') b ON a.Sid = b.Sid
JOIN
(SELECT * FROM sc WHERE Cid = '02') c ON b.Sid = c.Sid
WHERE b.score > c.score;

#JOIN 联合多表查询，分为3类：
INNER JOIN（内连接,或等值连接）：获取两个表中字段匹配关系的记录。(也可以省略 INNER 使用 JOIN，效果一样)
LEFT JOIN（左连接）：获取左表所有记录，即使右表没有对应匹配的记录。
RIGHT JOIN（右连接）： 与 LEFT JOIN 相反，用于获取右表所有记录，即使左表没有对应匹配的记录。
```



2、查询同时存在" 01 "课程和" 02 "课程的学生的信息

```mysql
# 方法一
mysql> SELECT a.*
    -> FROM student a
    -> JOIN sc b ON a.Sid = b.Sid
    -> JOIN sc c ON b.Sid = c.Sid
    -> WHERE b.Cid = '01'
    -> AND c.Cid = '02';

# 方法二
mysql> select a.*
    -> from student a
    -> join (select * from sc where Cid = '01') b on a.Sid = b.Sid
    -> join (select * from sc where Cid = '02') c on b.Sid = c.Sid;
```



3、查询存在" 01 "课程但可能不存在"02 "课程的学生成绩情况(不存在时显示为 null )

```mysql
mysql> select *
    -> from
    -> (select * from sc where Cid = '01') a
    -> left join
    -> (select * from sc where Cid = '02') b
    -> on a.Sid = b.Sid;
```



4、查询不存在" 01 "课程但存在" 02 "课程的学生成绩情况

```mysql
mysql> select *
    -> from sc
    -> where Cid = '02'
    -> and Sid not in # not in用法
    -> (select Sid from sc where Cid = '01');
```



5、查询平均成绩大于等于 60 分的同学的学生编号，学生姓名和平均成绩

```mysql
SELECT
  A.SID,
  B.Sname,
  A.平均成绩
FROM
  (
    SELECT  SID,AVG (score) 平均成绩
    FROM  SC GROUP BY  SID
    HAVING AVG(score)>=60
  ) A
JOIN Student B ON A.SID = B.SID
```



6、查询在 SC 表存在成绩的学生信息

```mysql
mysql> select *
    -> from student
    -> where
    -> Sid in (select distinct Sid from sc);
# SQL DISTINCT 关键字同 SELECT 语句一起使用，可以去除所有重复记录，只返回唯一项。
SELECT DISTINCT column1, column2,.....columnN 
FROM table_name
WHERE [condition]
```



7、查询所有同学的学生编号、学生姓名、选课总数、所有课程的总成绩(没成绩的显示为 null )

```mysql
mysql> select a.Sid, a.Sname, b.Cnt, b.total
    -> from student a
    -> left join(
    -> select Sid, count(Cid) Cnt, sum(score) total
    -> from sc
    -> group by Sid
    -> ) b on a.Sid = b.Sid;
```



8、查询有成绩的学生的信息，包括学生编号、学生姓名、选课总数、所有课程的总成绩

```mysql
mysql> select a.Sid, a.Sname, b.Cnt, b.total
    -> from student a
    -> right join(
    -> select Sid, count(Cid) Cnt, sum(score) total
    -> from sc
    -> group by Sid
    -> ) b on a.Sid = b.Sid;
```



9、查询「李」姓老师的数量 

```mysql
SELECT
  COUNT (*) 	#李姓老师数量
FROM  Teacher
WHERE  Tname LIKE '李%'
```



10、查询学过「张三」老师授课的同学的信息 

```mysql
mysql> select * from student
    -> where Sid in(
    -> select distinct Sid from sc a
    -> join course b on a.Cid = b.Cid
    -> join teacher c on b.Tid = c.Tid
    -> where c.Tname = '张三');
```



11. 查询没有学全所有课程的同学的信息 

```mysql
SELECT * FROM Student
WHERE SID IN 
(
SELECT  SID  FROM SC
GROUP BY  SID
HAVING COUNT (CID) < 3
)
```



12. 查询至少有一门课与学号为" 01 "的同学所学相同的同学的信息 

```mysql
mysql> select * from student
    -> where Sid in (
    -> select distinct Sid from sc
    -> where Cid in
    -> (select Cid from sc where Sid = '01')
    -> );
```



13. 查询和" 01 "号的同学学习的课程完全相同的其他同学的信息 

```mysql
mysql> select * from student
    -> where Sid in (
    -> select Sid from sc where Cid in
    -> (select distinct Cid from sc where Sid = '01')
    -> and Sid <> '01' 
    -> group by Sid
    -> having count(Cid)=3);
# <> 是 > 和 < 的条件都要，即 !=
```



14. 查询没学过"张三"老师讲授的任一门课程的学生姓名 

```mysql
mysql> select Sname from student
    -> where Sid not in(
    -> select distinct Sid from sc a
    -> join course b on a.Cid = b.Cid
    -> join teacher c on b.Tid = c.Tid
    -> where c.Tname = '张三');
```



15. 查询两门及其以上不及格课程的同学的学号，姓名及其平均成绩 

```mysql
mysql> select a.Sid, a.Sname, b.平均成绩
    -> from student a
    -> right join(
    -> select Sid, avg(score) 平均成绩 from sc
    -> where score<60
    -> group by Sid
    -> having count(score)>=2
    -> ) b on a.Sid = b.Sid;
```



16. 检索" 01 "课程分数小于 60，按分数降序排列的学生信息

```mysql
mysql> select a.*, b.score from student a
    -> join sc b on a.Sid = b.Sid
    -> where Cid = '01' and score < 60
    -> order by score desc;
```



17. 按平均成绩从高到低显示所有学生的所有课程的成绩以及平均成绩

```mysql
mysql> select Sid,
    -> max(case Cid when '01' then score else 0 end) '01',
    -> max(case Cid when '02' then score else 0 end) '02',
    -> max(case Cid when '03' then score else 0 end) '03',
    -> avg(score) 平均分 from sc
    -> group by Sid order by 平均分 desc;
```



18. 查询各科成绩最高分、最低分和平均分：

以如下形式显示：课程 ID，课程 name，最高分，最低分，平均分，及格率，中等率，优良率，优秀率

及格为>=60，中等为：70-80，优良为：80-90，优秀为：>=90

```sql
--SQL Server的解法
SELECT DISTINCT A.CID,Cname,最高分,最低分,平均分,及格率,中等率,优良率,优秀率 FROM SC A
LEFT JOIN Course on A.CID=Course.CID
LEFT JOIN (SELECT CID,MAX(score)最高分,MIN(score)最低分,AVG(score)平均分 FROM SC GROUP BY CID)B on A.CID=B.CID
LEFT JOIN (SELECT CID,(convert(decimal(5,2),(sum(case when score>=60 then 1 else 0 end)*1.00)/COUNT(*))*100)及格率 FROM SC GROUP BY CID)C on A.CID=C.CID
LEFT JOIN (SELECT CID,(convert(decimal(5,2),(sum(case when score >=70 and score<80 then 1 else 0 end)*1.00)/COUNT(*))*100)中等率 FROM SC GROUP BY CID)D on A.CID=D.CID
LEFT JOIN (SELECT CID,(convert(decimal(5,2),(sum(case when score >=80 and score<90 then 1 else 0 end)*1.00)/COUNT(*))*100)优良率 FROM SC GROUP BY CID)E on A.CID=E.CID
LEFT JOIN (SELECT CID,(convert(decimal(5,2),(sum(case when score >=90 then 1 else 0 end)*1.00)/COUNT(*))*100)优秀率
FROM SC GROUP BY CID)F on A.CID=F.CID
```



19. 按各科成绩进行排序，并显示排名， Score 重复时保留名次空缺 ？

```
SELECT *,RANK()over(order by score desc) 排名 FROM SC
```



20 按各科成绩进行排序，并显示排名， Score 重复时合并名次 ？

```
SELECT *,DENSE_RANK()over(order by score desc) 排名 FROM SC
```



21. 查询学生的总成绩，并进行排名，总分重复时保留名次空缺 ？

```
SELECT *,RANK()over(order by 总成绩 desc) 排名
FROM(
SELECT SID,SUM(score) 总成绩 FROM SC GROUP BY SID
)A
```



22 查询学生的总成绩，并进行排名，总分重复时不保留名次空缺 ？

```
SELECT *,DENSE_RANK()over(order by 总成绩 desc) 排名
FROM(
SELECT SID,SUM(score)总成绩 FROM SC GROUP BY SID
)A
```



23. 统计各科成绩各分数段人数：课程编号，课程名称，[100-85]，[85-70]，[70-60]，[60-0] 及所占百分比 ？

```
SELECT DISTINCT A.CID,B.Cname,C.[100-85],C.所占百分比,D.[85-70],D.所占百分比,E.[70-60],E.所占百分比,F.[60-0],F.所占百分比
FROM SC A
LEFT JOIN Course B ON A.CID=B.CID
LEFT JOIN (SELECT CID,sum(case when score>85 and score<=100 then 1 else null end) [100-85],
convert(decimal(5,2),(sum(case when score>85 and score<100 then 1 else null end))*1.00/COUNT(*))*100 所占百分比 FROM SC GROUP BY CID)C on A.CID=C.CID
LEFT JOIN (SELECT CID,sum(case when score>70 and score<=85 then 1 else null end)[85-70],
convert(decimal(5,2),(sum(case when score>70 and score<=85 then 1 else null end))*1.00/COUNT(*))*100 所占百分比 FROM SC GROUP BY CID)D on A.CID=D.CID
LEFT JOIN (SELECT CID,sum(case when score>60 and score<=70 then 1 else null end)[70-60],
convert(decimal(5,2),(sum(case when score>60 and score<=70 then 1 else null end))*1.00/COUNT(*))*100 所占百分比 FROM SC GROUP BY CID)E on A.CID=E.CID
LEFT JOIN (SELECT CID,sum(case when score>0 and score<=60 then 1 else null end)[60-0],
convert(decimal(5,2),(sum(case when score>0 and score<=60 then 1 else null end))*1.00/COUNT(*))*100 所占百分比 FROM SC GROUP BY CID)F on A.CID=F.CID
```



24. 查询各科成绩前三名的记录 ？

```
SELECT * FROM 
(SELECT *,rank()over (partition by CID order by score desc) A
FROM SC)B
WHERE B.A<=3
```



25. 查询每门课程被选修的学生数 

```mysql
mysql> select Cid, count(Sid) 学生数 from sc group by Cid;
```



#### 26 ~ 50

26、查询出只选修两门课程的学生学号和姓名 

```mysql
mysql> select Sid, Sname from student
    -> where Sid in (
    -> select Sid from
    -> (select Sid, count(Cid) 课程数 from sc group by Sid) a
    -> where a.课程数 = 2);
```



27、查询男生、女生人数

```mysql
mysql> select Ssex, count(Ssex) 人数
    -> from student group by Ssex;
```



28、查询名字中含有「风」字的学生信息

```mysql
mysql> select * from student
    -> where Sname like '%风%';
```



29、查询同名同性学生名单，并统计这些人数

```mysql
mysql> select a.*, b.人数
    -> from student a
    -> left join (
    -> select Sname, Ssex, count(*) 人数
    -> from student group by Sname, Ssex
    -> ) b on a.Sname = b.Sname and a.Ssex = b.Ssex
    -> where b.人数 > 1;
```



30、查询 1990 年出生的学生名单

```mysql
mysql> select * from student where year(Sage)=1990;
```



31、查询每门课程的平均成绩，结果按平均成绩降序排列，平均成绩相同时，按课程编号升序排列

```mysql
mysql> select Cid, avg(score) 平均成绩 from sc
    -> group by Cid order by 平均成绩 desc, Cid;
```



32、查询平均成绩大于等于 85 的所有学生的学号、姓名和平均成绩 

```mysql
mysql> select a.Sid, a.Sname, b.平均成绩 from student a
    -> left join (
    -> select Sid, avg(score) 平均成绩
    -> from sc group by Sid
    -> ) b on a.Sid = b.Sid
    -> where b.平均成绩 > 85;
```



33、查询课程名称为「数学」，且分数低于 60 的学生姓名和分数

```mysql
mysql> select a.Sname, b.score from (
    -> select * from sc where score < 60 and Cid =
    -> (select Cid from course where Cname = '数学')
    -> ) b
    -> left join student a on a.Sid = b.Sid;
```



34、查询所有学生的课程及分数情况（存在学生没成绩，没选课的情况）

```mysql
mysql> select a.Sid, b.Cid, b.score from student a
    -> left join sc b on a.Sid = b.Sid;
```



35、查询任何一门课程成绩在 70 分以上的姓名、课程名称和分数

```mysql
mysql> select a.Sname, b.Cname, b.score from (
    -> select c.*, d.Cname from
    -> (select * from sc where score > 70) c
    -> left join course d on c.Cid = d.Cid ) b
    -> left join student a on b.Sid = a.Sid;
```



36、查询不及格的课程学生姓名，课程名及分数

```mysql
mysql> select a.Sname, b.Cname, c.score from sc c
    -> join course b on c.Cid = b.Cid
    -> join student a on c.Sid = a.Sid
    -> where c.score < 60;
```



37、查询课程编号为01且课程成绩在80分以上的学生的学号和姓名

```mysql
mysql> select a.Sid, b.Sname from (
    -> select * from sc where score > 80 and Cid = '01'
    -> ) a left join student b on a.Sid = b.Sid;
```



38、求每门课程的学生人数（假设每个学生都有参加考试且有成绩）

```mysql
mysql> select Cid, count(*) 学生人数
    -> from sc group by Cid;
```



39、成绩不重复，查询选修「张三」老师所授课程的学生中，成绩最高的学生信息及其成绩 ？

```
SELECT TOP 1 * FROM SC
WHERE CID=
(SELECT CID
FROM Course
WHERE TID=
(SELECT TID FROM Teacher
WHERE Tname='张三'
)
)
ORDER BY score DESC
```



40、成绩有重复的情况下，查询选修「张三」老师所授课程的学生中，成绩最高的学生信息及其成绩 ？

```
SELECT * FROM 
( SELECT *,DENSE_RANK()OVER(ORDER BY score DESC) A
FROM SC
WHERE CID=
(
SELECT CID FROM Course
WHERE TID=
(SELECT TID FROM Teacher
WHERE Tname='张三'
)
)
)B
WHERE B.A=1
```



41、查询每门功成绩最好的前两名 ？

```
SELECT * FROM
(SELECT *,ROW_NUMBER()OVER (PARTITION BY CID ORDER BY score DESC)A
FROM SC
)B
WHERE B.A<3
```



42、统计每门课程的学生选修人数（超过5人的课程才统计），要求输出课程号和选修人数，查询结果按人数降序排列，若人数相同，按课程号升序排列

```mysql
mysql> select Cid, count(Sid) 选修人数
    -> from sc
    -> group by Cid
    -> having count(Sid)>5
    -> order by 选修人数 desc, Cid;
```



43、检索至少选修两门课程的学生学号 

```mysql
mysql> select Sid from sc
    -> group by Sid
    -> having count(Cid)>=2;
```



44、查询选修了全部课程的学生信息

```mysql
mysql> select Sid from sc
    -> group by Sid
    -> having count(Cid) =
    -> (select distinct count(1) a from course);
# count(1) 相当于 count(*)
```



45、查询各学生的年龄，只按年份来算 ？

```
SELECT SID,DATEDIFF(Year,Sage,GETDATE()) 年龄
FROM Student
```



46、按照出生日期来算，当前月日小于出生日期的月日则年龄减1岁 ？

```
SELECT *,
(CASE WHEN  
CONVERT(INT,'1'+SUBSTRING(CONVERT(VARCHAR(10),Sage,112),5,8))
 < CONVERT(int,'1'+SUBSTRING(CONVERT(VARCHAR(10),GETDATE(),112),5,8))
THEN DATEDIFF(YY,Sage,GETDATE())
ELSE DATEDIFF(YY,Sage,GETDATE())-1 
END
)age
FROM Student
```



47、查询本周过生日的学生 ？

```
SELECT *,(
CASE WHEN DATENAME(wk,CONVERT
(DATETIME,
(CONVERT(VARCHAR(10),YEAR(GETDATE()))
+SUBSTRING(CONVERT(VARCHAR(10),Sage,112),5,8)
)
)
)=DATENAME(WK,GETDATE())
THEN 1 ELSE 0 END
) 生日提醒
FROM Student
```



48、查询下周过生日的学生 ？

```
SELECT *,(
CASE WHEN DATENAME(wk,CONVERT
(DATETIME,
(CONVERT(VARCHAR(10),YEAR(GETDATE()))
+SUBSTRING(CONVERT(VARCHAR(10),Sage,112),5,8)
)
)
)=DATENAME(WK,GETDATE())+1
THEN 1 ELSE 0 END
) 生日提醒
FROM Student
```



49、查询本月过生日的学生 ？

```
SELECT *,(
CASE WHEN MONTH(
CONVERT(DATETIME,
(CONVERT(VARCHAR(10),YEAR(GETDATE()))
+SUBSTRING(CONVERT(VARCHAR(10),Sage,112),5,8)
)
)
)=MONTH(GETDATE())
THEN 1 ELSE 0 end) 生日提醒
FROM Student
```



50、查询下月过生日的学生 ？

```
SELECT *,(
CASE WHEN MONTH(
CONVERT(DATETIME,
(CONVERT(VARCHAR(10),YEAR(GETDATE()))
+SUBSTRING(CONVERT(VARCHAR(10),Sage,112),5,8)
)
)
)=MONTH(GETDATE())+1
then 1 else 0 end)生日提醒
FROM Student
```



