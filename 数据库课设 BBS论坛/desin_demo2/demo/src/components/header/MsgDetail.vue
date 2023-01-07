<template>
	<div class="msgd">
		<div class="uih">{{ nickname }}</div>
		<div class="connn">
			<div v-for="(value,index) in msg" class="msgt">
				{{ value }}
			</div>
		</div>
		<div class="send">
			<input type="text">
			<button>发送</button>
		</div>
	</div>
</template>

<script>
	export default{
		name:'MsgDetail',
		data() {
			return{
				nickname:this.$route.query.nickname,
				msg:[
					'消息1',
					'消息2',
					'消息1',
					'消息1',
					'消息1',
					'消息1',
					'消息1',
					'消息1',
					'消息1',
					'消息1',
					'消息1',
					'消息1'
				]
			}
		}
	}
</script>

<style scoped>
	.msgd{
		position: relative;
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		width: 80%;
		height: 100%;
		overflow: auto;
		border: 2px red solid;
	}
	.uih{
		position: absolute;
		top: 0;
		width: 100%;
		height: 1.875rem;
		background-color: aquamarine;
	}
	.connn{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		width: 100%;
		margin-top: 2.5rem;
	}
	.msgt{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		width: 100%;
	}
	.send{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		margin-top: 1.25rem;
		width: 100%;
		height: 2.5rem;
	}
	input{
		flex: 6;
		height: 100%;
	}
	button{
		flex: 1;
		height: 100%;
	}
</style>