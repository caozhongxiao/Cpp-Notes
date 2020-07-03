[TOC]

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

<img src="https://mmbiz.qpic.cn/mmbiz_png/icbViakEeV5qEEkc0pictl41nhRAHjNRUgN4KKZ3C4m9T0abD1Ym8GGEpRDNuwgcSWUQqEuAMm8LnjnQ3TLChTCdQ/640?wx_fmt=png&amp;tp=webp&amp;wxfrom=5&amp;wx_lazy=1&amp;wx_co=1" alt="img" style="zoom:67%;" />

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
(SELECT * FROM sc WHERE Cid = '02') c ON a.Sid = c.Sid
WHERE b.score > c.score;

#JOIN 联合多表查询，分为3类：
INNER JOIN（内连接,或等值连接）：获取两个表中字段匹配关系的记录。(也可以省略 INNER 使用 JOIN，效果一样)
LEFT JOIN（左连接）：获取左表所有记录，即使右表没有对应匹配的记录。
RIGHT JOIN（右连接）： 与 LEFT JOIN 相反，用于获取右表所有记录，即使左表没有对应匹配的记录。
```



2、查询同时存在" 01 "课程和" 02 "课程的学生的信息

```mysql
# 方法一
SELECT A.*
FROM Student A
JOIN SC B ON A.SID=B.SID
JOIN SC C ON C.SID=B.SID
WHERE B.CID='01'
AND C.CID='02'

# 方法二
SELECT A.*
FROM Student A
JOIN (SELECT * FROM SC WHERE CID = '01') B ON A.SID = B.SID
JOIN (SELECT * FROM SC WHERE CID = '02') C ON A.SID = C.SID
```



3、查询存在" 01 "课程但可能不存在"02 "课程的情况(不存在时显示为 null )

```
SELECT
  *
FROM
(SELECT * FROM SC WHERE CID = '01') A
LEFT JOIN 
(SELECT * FROM SC WHERE CID = '02') B ON A.SID = B.SID
```



4、查询不存在" 01 "课程但存在"02 "课程的情况

```
SELECT  *
FROM  SC
WHERE  CID = '02'
AND SID NOT IN (
  SELECT  SID FROM SC
  WHERE CID = '01'
)
```



5、查询平均成绩大于等于 60 分的同学的学生编号和学生姓名和平均成绩

```
SELECT
  A.SID,
  B.Sname,
  A.dc
FROM
  (
    SELECT  SID,AVG (score) dc
    FROM  SC GROUP BY  SID
    HAVING AVG(score)>=60
  ) A
JOIN Student B ON A.SID = B.SID
```



6、查询在 SC 表存在成绩的学生信息

```
SELECT
  *
FROM
  Student
WHERE
  SID IN (SELECT DISTINCT SID FROM SC)
```



7、查询所有同学的学生编号、学生姓名、选课总数、所有课程的总成绩(没成绩的显示为 null )

```
SELECT
  A.SID,
  A.Sname,
  B.Cnt,
  B.Total
FROM Student A
LEFT JOIN 
(
    SELECT
      SID,
      COUNT (CID) Cnt,
      SUM (score) Total
    FROM  SC
    GROUP BY SID
  ) B ON A.SID = B.SID
```



8、查有成绩的学生信息

```
SELECT
  A.SID,
  A.Sname,
  B.Cnt,
  B.Total
FROM Student A
RIGHT JOIN 
(
    SELECT
      SID,
      COUNT (CID) Cnt,
      SUM (score) Total
    FROM  SC
    GROUP BY SID
  ) B ON A.SID = B.SID
```



9、查询「李」姓老师的数量 

```
SELECT
  COUNT (*) 李姓老师数量
FROM  Teacher
WHERE  Tname LIKE '李%'
```



10、查询学过「张三」老师授课的同学的信息 

```
SELECT * FROM Student
WHERE SID IN 
(select DISTINCT SID FROM SC a
JOIN Course b ON a.cid=b.cid
JOIN Teacher c ON b.Tid=c.Tid
WHERE c.Tname='张三')
```



\11. 查询没有学全所有课程的同学的信息 

```
SELECT  * FROM  Student
WHERE  SID IN 
(
SELECT  SID  FROM SC
GROUP BY  SID
HAVING COUNT (CID) < 3
)
```



\12. 查询至少有一门课与学号为" 01 "的同学所学相同的同学的信息 

```
SELECT  *
FROM  Student
WHERE  SID IN (
SELECT DISTINCT  SID
FROM SC
WHERE  CID IN 
(
SELECT CID
FROM SC
WHERE SID = '01'
 )
)
```



\13. 查询和" 01 "号的同学学习的课程完全相同的其他同学的信息 

```
SELECT * FROM Student
WHERE SID in (
SELECT SID FROM SC WHERE CID in 
(SELECT DISTINCT CID FROM SC WHERE SID='01') and SID<>'01'
GROUP BY SID
having COUNT(CID) =3)
```



\14. 查询没学过"张三"老师讲授的任一门课程的学生姓名 

```
SELECT * FROM Student
WHERE SID NOT IN 
(select DISTINCT SID FROM SC a
JOIN Course b ON a.cid=b.cid
JOIN Teacher c ON b.Tid=c.Tid
WHERE c.Tname='张三')
```



\15. 查询两门及其以上不及格课程的同学的学号，姓名及其平均成绩 

```
SELECT A.SID,A.Sname,B.平均成绩
FROM Student A
RIGHT JOIN
(SELECT SID,AVG(score)平均成绩 FROM SC
WHERE score<60 
GROUP BY SID 
HAVING COUNT(score)>=2
)B
on A.SID=B.SID
```



\16. 检索" 01 "课程分数小于 60，按分数降序排列的学生信息

```
SELECT A.*,B.score FROM 
Student A
JOIN SC B ON A.SID=B.SID
WHERE CID='01' AND Score<60 
ORDER BY score DESC
```





\17. 按平均成绩从高到低显示所有学生的所有课程的成绩以及平均成绩

```
SELECT SID,
MAX(case CID when '01' then score else 0 end) '01',
MAX(case CID when '02' then score else 0 end)'02',
MAX(case CID when '03' then score else 0 end)'03',
AVG(score)平均分 FROM SC
GROUP BY SID ORDER BY 平均分 DESC
```





\18. 查询各科成绩最高分、最低分和平均分：

以如下形式显示：课程 ID，课程 name，最高分，最低分，平均分，及格率，中等率，优良率，优秀率

及格为>=60，中等为：70-80，优良为：80-90，优秀为：>=90

```
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

（提示：可以左右滑动代码）



\19. 按各科成绩进行排序，并显示排名， Score 重复时保留名次空缺

```
SELECT *,RANK()over(order by score desc) 排名 FROM SC
```



20 按各科成绩进行排序，并显示排名， Score 重复时合并名次

```
SELECT *,DENSE_RANK()over(order by score desc) 排名 FROM SC
```



\21.  查询学生的总成绩，并进行排名，总分重复时保留名次空缺

```
SELECT *,RANK()over(order by 总成绩 desc) 排名
FROM(
SELECT SID,SUM(score) 总成绩 FROM SC GROUP BY SID
)A
```





22 查询学生的总成绩，并进行排名，总分重复时不保留名次空缺

```
SELECT *,DENSE_RANK()over(order by 总成绩 desc) 排名
FROM(
SELECT SID,SUM(score)总成绩 FROM SC GROUP BY SID
)A
```



\23. 统计各科成绩各分数段人数：课程编号，课程名称，[100-85]，[85-70]，[70-60]，[60-0] 及所占百分比

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



\24. 查询各科成绩前三名的记录

```
SELECT * FROM 
(SELECT *,rank()over (partition by CID order by score desc) A
FROM SC)B
WHERE B.A<=3
```



\25. 查询每门课程被选修的学生数 

```
SELECT CID,COUNT(SID)学生数 FROM SC GROUP BY CID
```





