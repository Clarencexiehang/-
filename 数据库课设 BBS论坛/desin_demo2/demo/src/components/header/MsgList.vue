<template>
	<div class="msgl">
		<div v-for="(value,index) in msg" class="msgitem" @click="enterCom(value.nickname)">
			<div class="ii">{{ value.nickname }}</div>
			<div class="cc">
				{{ value.content }}
			</div>
			<div class="tt">
				{{ value.posttime }}
			</div>
		</div>
	</div>
</template>

<script>
	export default{
		name:'MsgList',
		data() {
			return{
				msg:[
					{
						nickname:'用户1',
						content:'消息1',
						posttime:'2022.12.4'
					},
					{
						nickname:'用户2',
						content:'消息2',
						posttime:'2022.12.4'
					}
				]
			}
		},
		methods:{
			enterCom(nickname){
				this.$router.push({
					name:'msgdetail',
					query:{
						nickname:nickname
					}
				})
			}
		}
		
	}
</script>

<style scoped>
	.msgl{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		width: 80%;
		height: 100%;
	}
	.msgitem{
		margin-top: 0.625rem;
		width: 90%;
		height: 4.125rem;
		border: 2px red solid;
		padding: 1.25rem;
		border-radius: 5px 5px;
	}
	.ii{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		border-bottom: 2px gray solid;
	}
	.cc{
		color: gray;
	}
	.tt{
		display: flex;
		flex-direction: row;
		justify-content: flex-end;
		align-items: center;
		color: gray;
		margin-right: 0.625rem;
	}
</style>