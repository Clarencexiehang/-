<template>
	<div id="article_detail">
		<!-- 帖子的用户信息 -->
		<span class="use_info">
			<span id="info">
				<span id="head">
					<img class="headimg" v-bind:src="headpath" alt="头像">
				</span>
				<span class="use_item">
					<label class="label">昵称:</label> 
					<span class="cont">
						{{ nickname }}
					</span>
				</span>
				<span class="use_item">
					<label class="label">账号:</label>
					<span class="cont">
						{{ acountname }}
					</span>
				</span>
				<span class="use_item">
					<label class="label">文章:</label>
					<span class="cont">
						{{ articleNum }}
					</span>
				</span>
				<span class="use_item">
					<label class="label">关注:</label>
					<span class="cont">
						{{ careNum }}
					</span>
				</span>
				<span class="user_op">
					<button v-if="isMyself" class="myself" disabled>我自己</button>
					<button v-else-if="!this.hasBecare" id="nocare" @click="CareUser(acountname)">关 &nbsp;&nbsp;注</button>
					<button v-else id="care">已 &nbsp;&nbsp;关 &nbsp;&nbsp;注</button>
					
					<button v-if="isMyself" class="myself1" disabled>私 &nbsp;&nbsp;信</button>
					<button v-else class="sendB" @click="privateSeng($event)">私 &nbsp;&nbsp;信</button>
				</span>
			</span>
		</span>
		
		<!-- 帖子信息 -->
		<span class="article">
			<div class="title">
				<h4>{{ title }}</h4>
			</div>
			<div class="content">
				<div class="con">
					{{ articleContent }}
				</div>
				<br>
				<br>
				<div class="agr" @click="articleAgree">
					点赞数
					<i class="el-icon-s-opportunity" title="点赞">: {{ agreeNum }}</i>
				</div>
			
				<div  v-if="showComments" class="showComments" @click="showComments=!showComments">
					<label for="hidden">收起评论 <i id="hidden" class="el-icon-caret-bottom"></i></label>
				</div>
				<div  v-else class="showComments" @click="showComments=!showComments">
					<label for="show">展开 {{ commentNum }} 条评论 <i id="show" class="el-icon-caret-right"></i></label>
				</div>
				
				<!-- 帖子评论 -->
				<div v-if="showComments" class="comments_div">
					<div v-for="(value,index1) in commentsInfo" class="comm_item">
						<div class="comm_use_info">
							<span class="comm_use_head">
								<img class="headimg" v-bind:src="value.com_headpath" alt="头像">
							</span>
							<span class="comm_use_nickname">
								{{ value.com_nickname }}
							</span>
							<span class="publish_time">
								{{ value.publish_time }}
							</span>
						</div>
						<div class="con">
							{{ value.content }}
						</div>
						<div class="agree_info">
							<i class="el-icon-s-opportunity" title="点赞" @click="Agree(index1,value.com_id)">{{ value.agreeNum }}</i>
							<i class="el-icon-s-comment" title="评论" @click="value.showReplay=!value.showReplay">{{ value.replayNum }}</i>
							<i class="el-icon-edit" title="回复" @click="value.showReplayEdit=!value.showReplayEdit"></i>
							<textarea v-if="value.showReplayEdit" v-model="value.publish_content" class="replay_edit" type="text" placeholder="回复楼主" cols="30" rows="10"></textarea>
							<button v-if="value.showReplayEdit" class="publish" @click="replayMainComment($event,index1,value.publish_content,value.com_id)">回复楼主</button>
							
							<button v-if="value.isMyself" class="del_com" @click="del_Com(index1,value.com_id)">删除</button>
						</div>
						
						<!-- 评论的回复 -->
						<div v-if="value.showReplay" class="replay">
							<!-- 每一条回复 -->
							<div v-for="(rep,index) in value.replayItem" class="replay_item">
								<div class="rep_use_info">
									<span class="rep_use_head">
										<img class="headimg" v-bind:src="rep.rep_headpath" alt="头像">
									</span>
									<span class="rep_use_nickname">
										{{ rep.rep_nickname }}
									</span>
									<span class="replay_type">回复 <mark>{{ rep.to_nickname }}</mark></span>
									<span class="publish_time">
										{{ rep.publish_time }}
									</span>
								</div>
								<div class="con">
									<p>{{ rep.content }}</p>
								</div>
								<div class="agree_info">
									<i class="el-icon-s-opportunity" title="点赞" @click="Agree2(index1,index,rep.rep_id)">{{ rep.agreeNum }}</i>
									<i class="el-icon-edit" title="回复" @click="rep.showReplayEdit=!rep.showReplayEdit"></i>
									<textarea v-if="rep.showReplayEdit" v-model="rep.publish_content" class="replay_edit" type="text" placeholder="回复 ta" cols="30" rows="10"></textarea>
									<button v-if="rep.showReplayEdit" class="publish" @click="replayNoMainComment($event,index1,index,rep.publish_content,rep.rep_id)">回复 ta</button>
									
									<button v-if="rep.isMyself" class="del_rep" @click="del_Rep(index1,index,rep.rep_id)">删除</button>
								</div>
							</div>
						</div>
					</div>
				</div>
			    <div class="publish_floor_comment">
			    	<textarea v-model="floorConmment" class="floor_comment" placeholder="发表文章评论" cols="30" rows="3"></textarea>
					<button class="publish" @click="publishMainComment">发表文章评论</button>
				</div>
			</div>
		</span>
	</div>
</template>

<script>
	import pubsub from 'pubsub-js'
	import axios from 'axios'
	import $ from 'jquery'
	
	
	export default{
		name:'ArticleDetail',
		data() {
			return{
				// 作者信息
				nickname:'',//文章作者昵称
				acountname:'',
				articleNum:'',
				careNum:'',
				headpath:require('../../assets/icon/head.png'),
				hasBecare:'',
				isMyself:false,
				
				// 文章信息
				title:'文章标题',
				articleContent:'文章内容',//显示文章的内容
				agreeNum:0,
				
				// 文章评论
				floorConmment:'',//文章新评论内容
				showComments:false,//是否显示评论
				
				//文章楼主评论信息
				commentsInfo:[
				],
				commentNum:0
			}
		},
		props:[
		  'cnickname','article_id'	
		],
		methods:{
			//  ********************** 挂载前执行,获取并设置用户昵称
			setUseName(){
				this.nickname=this.cnickname;
				
				console.log('-------------- ask ---------------');
				axios({
					url:'http://127.0.0.1:5000/user/userAllInfo',
					method:'post',
					data:{
						nickname:this.nickname
					}
					
				}).then((response)=>{
					console.log('-------------- mid ---------------');
					console.log(response.data.userinfo);
					
					this.nickname=response.data.userinfo.nickname;
					this.acountname=response.data.userinfo.acountname;
					this.articleNum=response.data.userinfo.articlenum;
					this.careNum=response.data.userinfo.carenum;
					if(this.acountname==window.sessionStorage.getItem('acountname')){
						this.isMyself=true;
					}
					
					// *********************************** 设置用户关注信息
					axios({
						url:'http://127.0.0.1:5000/article/careinfo',
						method:'post',
						data:{
							type:'get',
							care: window.sessionStorage.getItem('acountname'),
							becare:this.acountname
						}
						
					}).then((response1)=>{
						console.log('------------- 关注信息 status :  ',response1.data.status);
						if(response1.data.status=='exists'){
							console.log('------------- 该用户已被关注 ----------');
							this.hasBecare=true;
						}else{
							console.log('------------- 该用户未被关注 ----------');
							this.hasBecare=false;
						}
					}).catch(function(error){
						
					})
					
				}).catch(function(error){
					
				})
				
				// *********************************** 获取文章信息
				axios({
					url:'http://127.0.0.1:5000/article/getInfo',
					method:'post',
					data:{
						type:'getArtInfo',
						article_id:this.article_id
					}
					
				}).then((response)=>{
					console.log('------ 文章细节 ---------');
					console.log(response.data);
					this.title=response.data.title;
					this.articleContent=response.data.content;
					this.agreeNum=response.data.agreeNum;
				}).catch(function(error){
					
				})
				
				// ***************************** 获取评论信息
				axios({
					url:'http://127.0.0.1:5000/article/getInfo',
					method:'post',
					data:{
						type:'getCom',
						article_id:this.article_id
					}
				}).then((response)=>{
					console.log('ok------------ ',response.data);
					// 获取文章的楼主评论
					var replyInfo=response.data.replyInfo;
					for(var i=0;i<replyInfo.length;i++){
						var com={
									com_id:replyInfo[i].id,
									com_nickname:replyInfo[i].nickname,//用户昵称
									publish_time:replyInfo[i].replyTime,
									com_headpath:require('../../assets/icon/head.png'),//用户头像
									content:replyInfo[i].content,//评论内容
									agreeNum:replyInfo[i].likeNum,//点赞数
									
									showReplay:false,//是否显示评论回复
									showReplayEdit:false,//是否显示回复编辑框
									publish_content:'', //接收回复主评论的内容
									
									//楼主评论的回复区
									replayItem:[],
									replayNum:0,
									
									isMyself:false
							    }
						if(com.com_nickname==window.sessionStorage.getItem('nickname')){
							com.isMyself=true;
						}
						
						var repyTofloor=replyInfo[i].replyToFloor;
						for(var j=0;j<repyTofloor.length;j++){
							var rep={
								
								type:repyTofloor[j].replyType,  // 区分回复楼主还是非楼主
								rep_id:repyTofloor[j].id,
								rep_nickname:repyTofloor[j].nickname,//用户昵称
								to_nickname:repyTofloor[j].replyName,//回复对象
								rep_headpath:require('../../assets/icon/head.png'),
								publish_time:repyTofloor[j].replyTime,
								content:repyTofloor[j].content,//回复内容
								
								showReplayEdit:false,//是否显示回复编辑框
								publish_content:'',//接收回复非主评论的内容
								agreeNum:repyTofloor[j].likeNum,//点赞数
								
								isMyself:false
							}
							
							if(rep.rep_nickname==window.sessionStorage.getItem('nickname')){
								rep.isMyself=true;
							}
							
							com.replayItem.push(rep);
						}
						
						com.replayNum=com.replayItem.length;
						this.commentsInfo.push(com);
						this.commentNum=this.commentNum+1;
					}
					
				}).catch(function(error){
					
				})
				console.log('----------- *********** ',this.commentNum);
			},
			articleAgree(){
				// 文章点赞
				this.agreeNum=this.agreeNum+1;
				console.log('--------- 文章 iiiiiiii   点赞 +1');
				axios({
					url:'http://127.0.0.1:5000/article/addartagreenum',
					method:'post',
					data:{
						article_id:this.article_id
					}
					
				}).then((response)=>{
					console.log(response.data);
				}).catch(function(error){
					
				})
			},
			Agree(index,com_id){
				// 楼主评论点赞
				var n=this.commentsInfo[index].agreeNum;
				axios({
					url:'http://127.0.0.1:5000/article/addcomagreenum',
					method:'post',
					data:{
						reply_id:com_id
					}
					
				}).then((response)=>{
					this.commentsInfo[index].agreeNum=n+1;
				}).catch(function(error){
					
				})
			},
			Agree2(index1,index,id){
				// 非楼主评论点赞
				console.log('文章 ',index1,'  ',index,'   ',id,'  点赞 ');
				var n=this.commentsInfo[index1].replayItem[index].agreeNum;
				axios({
					url:'http://127.0.0.1:5000/article/addcomagreenum',
					method:'post',
					data:{
						reply_id:id
					}
					
				}).then((response)=>{
					this.commentsInfo[index1].replayItem[index].agreeNum=n+1;
				}).catch(function(error){
					
				})
			},
			publishMainComment(){
				// 发表楼主评论
				console.log('------ 发表楼主评论 ------- ',this.floorConmment);
				var time=new Date();
				var newComment={
						com_nickname:this.nickname,
						publish_time:{
							year:time.getFullYear(),
							month:time.getMonth(),
							day:time.getDay(),
							hour:time.getHours(),
							min:time.getMinutes(),
							sec:time.getSeconds()
						},
						com_headpath:require('../../assets/icon/head.png'),
						content:this.floorConmment,//从输入框接收评论内容
						agreeNum:0,
						showReplay:true,
						showReplayEdit:false,
						publish_content:'', //接收回复主评论的内容
						replayItem:[ //主评论的回复区
						],
						replayNum:0
					};
				
				this.commentsInfo.push(newComment);
				this.commentNum++;
				
				console.log('1111111111111111111111 : ',this.commentNum);
				// 数据库内添加新的评论
				axios({
					url:'http://127.0.0.1:5000/article/addrep',
					method:'post',
					data:{
						account: window.sessionStorage.getItem('acountname'),
						floorNum:this.commentNum,
						content:this.floorConmment,
						replyID :null,
						articleID :this.article_id
					}
					
				}).then((response)=>{
					
				}).catch(function(error){
					
				})
				
				this.floorConmment='';
				alert('发表评论成功 !');
				
			},
			replayMainComment($event,index,content,com_id){ 
				// 回复楼主
				console.log('+++++++++ 回复楼主 ',index,'  ',content,' ',com_id);
				
				var time=new Date();
				var newReplay={  // 新建楼主回复评论
					rep_nickname:this.nickname,
					to_nickname:'楼主',
					rep_headpath:require('../../assets/icon/head.png'),
					publish_time:{
						year:time.getFullYear(),
						month:time.getMonth(),
						day:time.getDay(),
						hour:time.getHours(),
						min:time.getMinutes(),
						sec:time.getSeconds()
					},
					content:content,
					showReplayEdit:false,
					agreeNum:0,
				};
				
				this.commentsInfo[index].replayItem.push(newReplay);
				
				// 数据库内添加新的评论
				axios({
					url:'http://127.0.0.1:5000/article/addrep',
					method:'post',
					data:{
						account: window.sessionStorage.getItem('acountname'),
						floorNum:index+1,
						content:content,
						replyID :com_id,
						articleID :this.article_id
					}
					
				}).then((response)=>{
					
				}).catch(function(error){
					
				})
				
				this.commentsInfo[index].publish_content='';
			},
			replayNoMainComment($event,index1,index,content,rep_id){
				// 回复非楼主
				/* console.log('回复 楼主 ： ',index1,' 的 第 ',index,' 个评论'); */
				var time=new Date();
				var newReplay={  // 新建回复
								type:'nofloorer',  // 回复非楼主
								rep_nickname:this.nickname,
								// 回复的用户名
								to_nickname:this.commentsInfo[index1].replayItem[index].rep_nickname,
								rep_headpath:require('../../assets/icon/head.png'),
								publish_time:{
									year:time.getFullYear(),
									month:time.getMonth(),
									day:time.getDay(),
									hour:time.getHours(),
									min:time.getMinutes(),
									sec:time.getSeconds()
								},
								content:content,
								showReplayEdit:false,
								publish_content:'',//接收回复非主评论的内容
								agreeNum:0,
							};
							
				this.commentsInfo[index1].replayItem.push(newReplay);
				
				// 数据库内添加新的评论
				axios({
					url:'http://127.0.0.1:5000/article/addrep',
					method:'post',
					data:{
						account: window.sessionStorage.getItem('acountname'),
						floorNum:index1+1,
						content:content,
						replyID :rep_id,
						articleID :this.article_id
					}
					
				}).then((response)=>{
					
				}).catch(function(error){
					
				})
				
				this.commentsInfo[index1].replayItem[index].publish_content='';
			},
			del_Com(index,com_id){
				console.log('=++++++++++++++ 删除楼主评论 : ',com_id);
				this.commentsInfo.splice(index,1);
				
				axios({
					url:'http://127.0.0.1:5000/article/delcom',
					method:'post',
					data:{
						com_id: com_id
					}
					
				}).then((response)=>{
					
				}).catch(function(error){
					
				})
			},
			del_Rep(index1,index,rep_id){
				console.log('=++++++++++++++ 删除评论回复 : ',rep_id);
				this.commentsInfo[index1].replayItem.splice(index,1);
				
				axios({
					url:'http://127.0.0.1:5000/article/delrep',
					method:'post',
					data:{
						rep_id: rep_id
					}
					
				}).then((response)=>{
					
				}).catch(function(error){
					
				})
			},
			Care(){
				$("#care").addClass("btnbc");
			},
			privateSeng($event){
				console.log('进入私信页面 ： ',this.nickname);
				this.$router.push({
									name:'msgdetail',
									query:{
										nickname:this.nickname
									}
								})
			},
			CareUser(acountname){
				console.log('  用户  ',window.sessionStorage.getItem('acountname'),'  关注  ',acountname);
				axios({
					url:'http://127.0.0.1:5000/user/addcare',
					method:'post',
					data:{
						care: window.sessionStorage.getItem('acountname'),
						becare:acountname
					}
					
				}).then((response)=>{
					
				}).catch(function(error){
					
				})
				
				alert('关注成功 !');
				
			}
		},
		beforeMount() {
		   console.log('--------- beforeMount --------  ');
		   this.setUseName();
		},
		mounted() {
			/* 插入新历史记录 */
			axios({
				url:'http://127.0.0.1:5000/user/posthistory',
				method:'post',
				data:{
					acountname:window.sessionStorage.getItem('acountname'),
					article_id:this.article_id
				}
			}).then((response)=>{
				
			}).catch((error)=>{
				
			})
		}
	}
</script>

<style scoped>
	#article_detail{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		width: 70%;
		height: 100%;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
		margin-top: 5px;
		
		background-color: wheat;
		overflow: auto;
	}
	
	.use_info{
		flex: 1;
		height: 100%;
		float: left;
		background-color: rgb(95, 158, 160);
	}
	
	.article{
		flex: 4;
		
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		height: 100%;
		float: left;
		margin-left: 0.625rem;
		
		overflow-y: auto;
		overflow: scroll;
		
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	
	#info{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		flex:1;
		
		height: 100%;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	#head{
		display: block;
		width: 100px;
		height: 100px;
		border: 4px solid gray;
		border-radius: 50% 50%;
	}
	.headimg{
		width: 100%;
	}
	
	.publish_time{
		font-size: 0.625rem;
		color: gray;
		margin-left: 1.25rem;
	}
	
	.use_item{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		width: 90%;
		height: 10%;
		float: left;
	}
	.label{
		font-weight:60 ;
		direction: ltr;
		
		flex: 2;
	}
	.cont{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		float: right;
		flex: 4;
		height: 50%;
		overflow: auto;
	}
	
	.con{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		flex-wrap: wrap;
		
		width: 100%;
	}
	#care{
		width: 45%;
		height: 100%;
		background-color: gray;
		color: white;
		font-size: 0.9375rem;
		border-radius: 0.25rem 0.25rem;
	}
	#nocare{
		width: 40%;
		height: 100%;
		background-color: royalblue;
		font-size: 0.9375rem;
		border-radius: 0.25rem 0.25rem;
	}
	.myself{
		width: 40%;
		height: 100%;
		background-color: gray;
		font-size: 0.9375rem;
		border-radius: 0.25rem 0.25rem;
		color: white;
	}
	.myself1{
		width: 40%;
		height: 100%;
		background-color: gray;
		font-size: 0.9375rem;
		border-radius: 0.25rem 0.25rem;
		color: white;
	}
	.sendB{
		width: 40%;
		height: 100%;
		background-color: royalblue;
		font-size: 0.9375rem;
		border-radius: 0.25rem 0.25rem;
	}
	.btnbc{
		background-color: darkgray;
	}
	.user_op{
		display: flex;
		flex-direction: row;
		justify-content: space-around;
		
		width: 100%;
		height: 2.125rem;
	}
	
	
	
	
	
	
	/* 文章部分 */
	.title{
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		height: 5%;
	}
	.content{
		width: 90%;
		height: 95%;
		margin-top: 0.625rem;
		border: 0.7px solid black;
		overflow: auto;
	}
	
	.agr{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		color: red;
		border-top: 2px gray solid;
	}
	/* 评论部分 */
	.publish_floor_comment{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		background-color: rgb(255, 255, 255);
		height: 3.125rem;
	}
	.floor_comment{
		width: 50%;
		height: 70%;
		margin-left: 20%;
	}
	.showComments{
		color: gray;
	}
	.comments_div{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: flex-start;
		
		width: 98%;
		
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	.comm_item{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		width: 100%;
	}
	.comm_item .con{
		width: 90%;
	}
	.comm_use_info{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		width: 100%;
		height: 50px;
	}
	.comm_use_head{
		width: 2.5rem;
		height: 2.5rem;
		border-radius: 50% 50%;
		border: 0.1875rem gray solid;
	}
	
	.agree_info{
		position: relative;
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		width: 100%;
		height: 50px;
		margin-top: 0.625rem;

		border: 0.7px gray solid;
		/* border-top: 1px gray solid; */
	}
	.agree_info i{
		margin-left: 1.875rem;
	}
	.replay_edit{
		width: 50%;
		height: 70%;
		margin-left: 0.625rem;
	}
	.publish{
		width: 20%;
		height: 60%;
		border: none;
		margin-left: 1.25rem;
		
		background-color: royalblue;
		color: white;
		font-size: 1.25rem;
	}
	.del_com{
		margin-left: 20px;
		border: none;
		color: red;
		font-size: 15px;
		background: transparent;
	}
	.del_rep{
		margin-left: 20px;
		border: none;
		color: red;
		font-size: 15px;
		background: transparent;
	}
	
		/* 评论回复部分 */
	.replay{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: flex-end;
		
		width: 98%;
		border: 1px gray solid;
	}

	.replay_item{
		width: 90%;
		margin-top: 0.625rem;
		border: 1px gray solid;
	}
	.replay_item .con{
		width: 90%;
		margin-left: 1.625rem;
	}
	.rep_use_info{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		width: 100%;
		height: 2.25rem;
	}
	.rep_use_head{
		width: 2rem;
		height: 2rem;
		border: 3px gray solid;
		border-radius: 50% 50%;
	}
	.replay_type{
		margin-left: 0.625rem;
		font-size: 0.625rem;
	}
	.replay_type mark{
		
		color: red;
		background: none;
	}
	
	
</style>