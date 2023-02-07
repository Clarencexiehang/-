<template>
	<div class="uadd">
		<div v-if="!hasArt" class="nodd">
			当前用户无发表记录 ！
		</div>
		<div v-else class="hasdd">
			<div v-for="(item,index) in useArt" class="itt">
				<div class="titlet">
					<h3>{{ item.title }}</h3>
				</div>
				<div class="contt">{{ item.content }}</div>
				<div class="oth">
					发表于 {{ item.posttime }}
					<i class="el-icon-s-opportunity" title="点赞" @click="addAgreeNum(index,value.article_id)">{{ item.agreenum }}</i>
				</div>
			</div>
		</div>
	</div>
</template>

<script>
	import axios from 'axios'
	export default{
		name:'UserArts',
		data() {
			return{
				nickname:'',
				useArt:[],
				hasArt:false
			}
		},
		mounted() {
			this.nickname=this.$route.query.nickname;
			
			axios({
				url:'http://127.0.0.1:5000/admin/getuserartbynickname',
				method:'post',
				data:{
					nickname:this.nickname
				}
			}).then((response)=>{
				if(response.data.hasArt=='no'){
					this.hasArt=false;
				}
				else{
					this.hasArt=true;
					this.useArt=[];
					var artList=response.data.useArt;
					for(var i=0;i<artList.length;i++){
						this.useArt.push(artList[i]);
					}
				}
			}).catch((error)=>{
				
			})
		},
		methods:{
			removeArt(index,article_id){
				var removeSure=confirm('确定删除用户的该帖子 ?');
				if(removeSure){
					console.log('删除用户帖子  ',index,'   ',article_id);
					this.useArt.splice(index,1);
					
					axios({
						url:'http://127.0.0.1:5000/admin/remartbyid',
						method:'post',
						data:{
							article_id:article_id
						}
					}).then((response)=>{
						if(response.data.status=='remok'){
							alert('该帖子已删除 !');
						}
					}).catch((error)=>{
						
					})
				}
			}
		}
	}
</script>

<style scoped>
	.uadd{
		width: 80%;
		height: 100%;
		overflow: auto;
	}
	.nodd{
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		width: 100%;
		height: 100%;
		color: red;
		font-family: '幼圆';
		font-size: 1.25rem;
	}
	.hasdd{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		width: 100%;
		height: 100%;
	}
	.itt{
		display: flex;
		flex-direction: column;
		justify-content: space-between;
		align-items: flex-start;
		
		padding: 0.625rem;
		width: 90%;
		height: auto;
		margin-top: 1.625rem;
		border-radius: 0.3125rem 0.3125rem;
		background-color: cadetblue;
	}
	.titlet{
		margin: 0.325rem;
		text-align: center;
		width: 100%;
		border-bottom: 2px gray solid;
	}
	.contt{
		margin: 0.325rem;
	}
	.oth{
		display: flex;
		width: 100%;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		margin-top: 20px;
		color: red;
	}
	.el-icon-s-opportunity{
		margin-left: 15px;
	}
	.oth button{
		background-color: red;
		color: white;
		margin: 0.625rem;
		padding: 0.3125rem;
		font-size: 0.9375rem;
		border: none;
	}
	.timee{
		font-size: 0.925rem;
	}
	
</style>