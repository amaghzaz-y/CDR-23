<script lang="ts">
	import { baseURL } from "$lib/store";
	import { Button, ButtonSet, NumberInput } from "carbon-components-svelte";
	import Calculation from "carbon-icons-svelte/lib/Calculation.svelte";
	let Distance = 0;
	let angle_w = 0;
	let Distance_M_1 = 0;
	let Distance_M_2 = 0;
	let Distance_M_3 = 0;
	let angle_1 = 0;
	let angle_2 = 0;
	let angle_3 = 0;
	const degrees_to_radians = (degrees: number) => {
		return degrees * (Math.PI / 180);
	};
	const computeD = () => {
		angle_1 = degrees_to_radians(angle_w - 90);
		angle_2 = degrees_to_radians(angle_w + 30);
		angle_3 = degrees_to_radians(angle_w + 150);
		Distance_M_1 = Distance * Math.sin(angle_1);
		Distance_M_2 = Distance * Math.sin(angle_2);
		Distance_M_3 = Distance * Math.sin(angle_3);
	};
	const reset = () => {
		Distance = 0;
		angle_w = 0;
		Distance_M_1 = 0;
		Distance_M_2 = 0;
		Distance_M_3 = 0;
		angle_1 = 0;
		angle_2 = 0;
		angle_3 = 0;
	};
	const execute = async () => {
		const url = `${baseURL}/steps/${Distance_M_1}/${Distance_M_2}/${Distance_M_3}`;
		await fetch(url);
	};
</script>

<div class="container">
	<div class="title">
		<h5>Steps Calculator</h5>
		<Calculation size={24} style="margin-inline: 1rem;" />
	</div>
	<NumberInput label="Distance" bind:value={Distance} step={100} />
	<NumberInput label="Angle" bind:value={angle_w} step={10} />
	<div class="button-set">
		<ButtonSet>
			<Button on:click={reset} kind="secondary">Reset</Button>
			<Button on:click={computeD}>Calculate</Button>
			<Button on:click={execute}>Execute</Button>
		</ButtonSet>
	</div>
	<div>
		Motor 1 : {Distance_M_1.toFixed(2)}
	</div>
	<div>
		Motor 2 : {Distance_M_2.toFixed(2)}
	</div>
	<div>
		Motor 3 : {Distance_M_3.toFixed(2)}
	</div>
</div>

<style scoped>
	.title {
		display: flex;
		justify-self: center;
		align-self: center;
		justify-content: center;
		align-items: center;
	}
	.container {
		display: flex;
		flex-direction: column;
		gap: 0.5rem;
		padding: 0.75rem;
	}
	.button-set {
		width: 6rem;
	}
</style>
