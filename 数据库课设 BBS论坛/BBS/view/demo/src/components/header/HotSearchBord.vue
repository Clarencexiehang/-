<template>
	<div id="hotsearch">
		<div class="ckk">
			<img :src="iconpath" class="htimg1" alt="热度">
			<h3>文章热榜</h3>
		</div>
		<div v-for="(value,index) in hotdata" class="itemm">
				 <span class="s1">
					 {{ index+1 }}
				 </span>
				 <span class="s2">
					 {{ value.title }}
				 </span>
				 <span class="s3">
					 <img :src="iconpath" title="热度" class="htimg" alt="热度">
					 {{ value.agreenum}}
				 </span>
		</div>
	</div>
</template>

<script>
	import axios from 'axios'
	export default{
		name:'HotSearchBord',
		data() {
			return {
				iconpath:require('../../assets/icon/lj.png'),
				hotdata:[
				]
			}
		},
		beforeMount() {
			axios({
				url:'http://127.0.0.1:5000/user/hotdata',
				method:'get'
			}).then((response)=>{
				console.log(response.data);
				var dd=response.data.hotdata;
				for(var i=0;i<dd.length;i++){
					var art={
						headpath:require('../../assets/icon/head.png'),
						article_id:dd[i].article_id,
						title:dd[i].title,
						content:dd[i].content,
						agreenum:dd[i].agreenum
					}
					this.hotdata.push(art);
				}
			}).catch(function(error){
			
			})
		}
	}
</script>

<style scoped>
	#hotsearch{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		width: 60%;
		height: 100%;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
		margin-top: 5px;
		overflow: auto;
	}
	.ckk{
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		width: 100%;
	}
	.htimg1{
		height: 30px;
		margin-right: 10px;
	}
	.itemm{
		display: flex;
		flex-direction: row;
		justify-content: space-between;
		align-items: center;

		margin-top: 0.625rem;
		width: 80%;
		height: 3.5rem;
		background-color: cornflowerblue;
		border-radius: 0.3125rem 0.3125rem;

	}
	.s1{
		padding: 1.3125rem;
	}
	.s2{
		width: 50%;
		overflow: auto;
		padding: 1.3125rem;

	}
	.s3{
		width: 20%;
		padding: 1.3125rem;
	}
	.htimg{
		width: 15%;
	}
</style>