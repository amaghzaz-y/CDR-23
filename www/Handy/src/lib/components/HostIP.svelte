<script>
	import { Button, ButtonSet, TextInput } from "carbon-components-svelte";
	import { HostIP } from "$lib/store";
	let standardIP = "192.168.4.1";
	const reset = () => {
		HostIP.set(standardIP);
	};
</script>

<div>
	<TextInput labelText={"ESP32 IP :"} inline bind:value={$HostIP} />
	<Button kind={"secondary"} size={"small"} on:click={reset}>Reset</Button>
</div>

<style scoped>
	div {
		display: flex;
		width: 28rem;
	}
</style>
