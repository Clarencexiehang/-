/************************* 建表 **************************/
create table announcement
(
   Aid                  int not null auto_increment,
   content              text,
   posttime             timestamp not null default CURRENT_TIMESTAMP,
   primary key (Aid)
);

create table article
(
   article_id           int not null auto_increment,
   id                   int,
   use_id               int,
   user_account         varchar(10),
   content              text,
   posttime             timestamp not null default CURRENT_TIMESTAMP,
   agreenum             int,
   title                text,
   primary key (article_id)
);

create table careandbecare
(
   care                 varchar(100) not null,
   becare               varchar(100) not null,
   id                   int,
   primary key (care, becare)
);

create table collect
(
   id                   int,
   art_article_id       int,
   account              varchar(20),
   article_id           int,
   collectTime          timestamp not null default CURRENT_TIMESTAMP
);

create table history
(
   art_article_id       int,
   id                   int,
   account              varchar(20),
   article_id           int,
   readtime             timestamp not null default CURRENT_TIMESTAMP
);

create table message
(
   id                   int not null auto_increment,
   use_id               int,
   reciever             varchar(10),
   content              varchar(1024),
   sender               varchar(10),
   sendTime             timestamp not null default CURRENT_TIMESTAMP,
   primary key (id)
);

create table reply
(
   id                   int not null auto_increment,
   use_id               int,
   floorNum             int,
   accountname          varchar(100),
   content              varchar(10000),
   replyID              int,
   article_id           int,
   replyTime            timestamp not null default CURRENT_TIMESTAMP,
   likeNum              int,
   primary key (id)
);

create table user
(
   id                   int not null auto_increment,
   acountname           varchar(100),
   nickname             varchar(100),
   email                varchar(100),
   phone                varchar(100),
   password             varchar(100),
   registertime         timestamp not null default CURRENT_TIMESTAMP,
   carenum              int,
   articlenum           int,
   age                  int,
   collectnum           int,
   primary key (id)
);

/************************* 表约束 *************************/
alter table article add constraint "FK_ÎÄÕÂÓë»Ø¸´-Ò»¶Ô¶à" foreign key (id)
      references reply (id) on delete restrict on update restrict;

alter table article add constraint FK_ÓÃ»§ÓëÎÄÕÂ foreign key (use_id)
      references user (id) on delete restrict on update restrict;

alter table careandbecare add constraint FK_ÓÃ»§¹Ø×¢¡ª¶à¶Ô¶à foreign key (id)
      references user (id) on delete restrict on update restrict;

alter table collect add constraint "FK_ÊÕ²ØÓëÎÄÕÂ-¶à¶ÔÒ»" foreign key (art_article_id)
      references article (article_id) on delete restrict on update restrict;

alter table collect add constraint "FK_ÊÕ²ØÓëÓÃ»§--¶à¶ÔÒ»" foreign key (id)
      references user (id) on delete restrict on update restrict;

alter table history add constraint FK_ÎÄÕÂÓëÀúÊ· foreign key (art_article_id)
      references article (article_id) on delete restrict on update restrict;

alter table history add constraint "FK_ÓÃ»§ÓëÀúÊ·-Ò»¶Ô¶à" foreign key (id)
      references user (id) on delete restrict on update restrict;

alter table message add constraint FK_ÓÃ»§ÏûÏ¢ foreign key (use_id)
      references user (id) on delete restrict on update restrict;

alter table reply add constraint FK_»Ø¸´ÓëÓÃ»§ foreign key (use_id)
      references user (id) on delete restrict on update restrict;


/************************* 触发器 *************************/
#用户文章数 +1 触发器 
delimiter $$
create trigger up_userAN after insert on article for each row
    update user set articlenum = articlenum+1 where acountname = NEW.user_account;
$$
delimiter ;


#用户文章数 -1 触发器 
delimiter $$
create trigger userAN_Sub after delete on article for each row
    update user set articlenum = articlenum-1 where acountname = OLD.user_account;
$$
delimiter ;


#关注用户相同限制    触发器
delimiter $$ 
create trigger con_Care before insert on careandbecare for each row
    if new.care=new.becare then 
         signal sqlstate 'HY003' set message_text='关注不合法 !';
    end if
$$
delimiter $$


#用户被关注数+1 触发器 
delimiter $$
create trigger up_userCN after insert on careandbecare for each row
    update user set carenum = carenum+1 where acountname = NEW.becare;
$$
delimiter ;


#用户被关注数-1  触发器 
delimiter $$
create trigger useBecareNum_Sub after delete on careandbecare for each row
    update user set carenum = carenum-1 where acountname = OLD.becare;
$$
delimiter ;


#用户收藏数 +1 触发器 
delimiter $$
create trigger collecNum_Add after insert on collect for each row
    update user set collectnum = collectnum+1 where acountname = NEW.account;
$$
delimiter ;


#用户收藏数 -1 触发器 
delimiter $$
create trigger collecNum_Sub after delete on collect for each row
    update user set collectnum = collectnum-1 where acountname = OLD.account;
$$
delimiter ;


/************************* 存储过程 *************************/
#获取所有人的昵称
delimiter $$ 
create procedure getAll_Nickname()
begin
    select nickname from user;
end
$$
delimiter $$

call getAll_Nickname();


#根据用户名搜索文章详情
delimiter $$ 
create procedure getArt_By_Nickname(in nnickname varchar(20))
begin
    set @acc=(select acountname from user where nickname=nnickname);
    select * from article where user_account=@acc;
end
$$
delimiter $$


#根据用户名搜索文章数
delimiter $$ 
create procedure getArtNum_By_Nickname(in nnickname varchar(20))
begin
    set @acc=(select acountname from user where nickname=nnickname);
    select count(*) from article where user_account=@acc;
end
$$
delimiter $$


#根据用户名搜索关注数
delimiter $$ 
create procedure getmyCareNum_By_Nickname(in nnickname varchar(20))
begin
    set @acc=(select acountname from user where nickname=nnickname);
    select count(*) from careandbecare where care=@acc;
end
$$
delimiter $$


#根据用户名搜索被关注数
delimiter $$ 
create procedure getbeCareNum_By_Nickname(in nnickname varchar(20))
begin
    set @acc=(select acountname from user where nickname=nnickname);
    select count(*) from careandbecare where becare=@acc;
end
$$
delimiter $$


#根据用户名搜索收藏数
delimiter $$ 
create procedure getcollecNum_By_Nickname(in nnickname varchar(20))
begin
    set @acc=(select acountname from user where nickname=nnickname);
    select count(*) from collect where account=@acc;
end
$$
delimiter $$


#根据用户名搜索历史记录数
delimiter $$ 
create procedure getHistNum_By_Nickname(in nnickname varchar(20))
begin
    set @acc=(select acountname from user where nickname=nnickname);
    select count(*) from history where account=@acc;
end
$$
delimiter $$

/************************* 创建视图 *************************/
create view us as select acountname,nickname,email,phone,password from user;
create view ar as select user_account,content,agreenum,title from article;
create view me as select sender,content,reciever from message;
create view re as select accountname,content,floorNum,likeNum from reply;
create view co as select account,article_id from collect;

/************************* 创建索引 *************************/
create index article_title_index
    on BBS2.article (title);
create index user_acountname_index
    on BBS2.user (acountname);
create index user_nickname_index
    on BBS2.user (nickname);
create index index_name
    on BBS2.article (user_account);
create index index_name
    on BBS2.article (posttime);
create index index_name
    on BBS2.reply (accountname);
create index index_name2
    on BBS2.reply (likeNum);
create index index_name
    on BBS2.message (sendTime);
create index history_readtime_index
    on BBS2.history (readtime);
create index index_name
    on BBS2.collect (account);
create index collect_collectTime_index
    on BBS2.collect (collectTime);


/************************* 数据库用户创建及授权 *************************/
create user admin identified by '123456';
grant all privileges on BBS2.article to admin;
grant execute on BBS2.* to admin;
grant all privileges on BBS2.announcement to admin;
flush privileges;






